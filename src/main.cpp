#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"
#include "pin_initializer.h"
#include "constants.h"

// Motion Sensor
unsigned long lastMotionTime = 0; // Timestamp of the last motion detected
int motionCount = 0;              // Counter for motion detections
bool motionCountExceeded = false; // Flag to track if motion count exceeded

// Pin Config
Scheduler scheduler(irrigationInterval);
PinInitializer pinInitializer;

// Lights
bool lightsAreOn = false;
unsigned long nextOnTime = 0;
unsigned long nextOffTime = 0;
unsigned long nextIrrigationTime = 0;
unsigned long previousMillis = 0;

// Motion
const unsigned long minMotionDuration = 2000;         // 2 seconds
unsigned long motionStartTimes[3] = {0, 0, 0};        // Track when motion started per PIR sensor
bool motionAlreadyCounted[3] = {false, false, false}; // prevent double-counting during continuous motion

// Voltage reading helper
float readVoltage()
{
  int adc = analogRead(VOLTAGE_SENSOR_PIN);
  float vin = (adc * VREF / 4095.0) * (R1 + R2) / R2 * VOLTAGE_CORRECTION;
  Serial.printf("Input Voltage = %.2fV\n", vin);
  return vin;
}

void setup()
{
  Serial.begin(115200);
  analogReadResolution(12); // Set ADC resolution for accurate readings

  // Initialize scheduler
  scheduler = Scheduler(irrigationInterval);
  scheduler.setIrrigationInterval(irrigationInterval);

  // Initialize pin configurations
  pinInitializer.setupSolenoidValvePins();
  pinInitializer.setupPIRSensorPins();
  pinInitializer.setupLightPins();

  unsigned long currentTime = millis();
  float vin = readVoltage(); // Read voltage at startup

  if (vin > MIN_REQUIRED_VOLTAGE)
  {
    // Turn on lights initially only if voltage is sufficient
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
      digitalWrite(LIGHT_PINS[i], HIGH);
    }
    lightsAreOn = true;
    previousMillis = currentTime;
    nextOffTime = currentTime + lightsIntervalOn;
    nextIrrigationTime = currentTime + initialIrrigationDelay;
    nextOnTime = currentTime + lightsCycleInterval; // Next lights in 24 hours
  }
  else
  {
    // Keep lights off and schedule next on time anyway
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
      digitalWrite(LIGHT_PINS[i], LOW);
    }
    lightsAreOn = false;
    nextOffTime = 0;
    nextIrrigationTime = 0;
    nextOnTime = currentTime + lightsCycleInterval; // Try again in 24 hours
  }
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  // Check if it's time for irrigation
  if (nextIrrigationTime > 0 && currentTime >= nextIrrigationTime)
  {
    runIrrigation();
    scheduler.setLastIrrigationRun(currentTime);
    nextIrrigationTime = currentTime + irrigationInterval; // Next irrigation
  }

  // Handle automated light scheduling
  if (lightsAreOn && (currentTime >= nextOffTime))
  {
    // Turn lights off
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
      digitalWrite(LIGHT_PINS[i], LOW);
    }
    lightsAreOn = false;
    previousMillis = currentTime;
  }
  else if (!lightsAreOn && (currentTime >= nextOnTime))
  {
    float vin = readVoltage();
    if (vin > MIN_REQUIRED_VOLTAGE)
    {
      // Turn lights on
      for (int i = 0; i < NUM_LIGHTS; i++)
      {
        digitalWrite(LIGHT_PINS[i], HIGH);
      }
      lightsAreOn = true;
      previousMillis = currentTime;
      nextOffTime = currentTime + lightsIntervalOn;
      nextOnTime = currentTime + lightsCycleInterval; // Next lights in 24 hours
    }
    else
    {
      // Skip light activation, retry in 24 hours
      nextOnTime = currentTime + lightsCycleInterval;
    }
  }

  // Check PIR sensor pins for sustained motion (per sensor)
  if (!motionCountExceeded)
  {
    for (int i = 0; i < 3; i++)
    {
      int sensorValue = digitalRead(PIR_SENSOR_PINS[i]);

      if (sensorValue == HIGH)
      {
        if (motionStartTimes[i] == 0)
        {
          motionStartTimes[i] = currentTime; // Start timing
        }
        else if (!motionAlreadyCounted[i] && (currentTime - motionStartTimes[i] >= minMotionDuration))
        {
          // Valid motion sustained on sensor i
          motionDetected = true;
          motionCount++;
          motionAlreadyCounted[i] = true;

          if (!motionCountExceeded && motionCount > 30)
          {
            motionCountExceeded = true;
            lastMotionTime = currentTime;
          }

          // Trigger sprinklers based on sensor index
          switch (i)
          {
          case 0:
            motionControlledSprinkler(4); // Middle
            motionControlledSprinkler(5); // Left
            break;
          case 1:
            motionControlledSprinkler(9); // MiddleRight
            motionControlledSprinkler(3); // Right
            break;
          case 2:
            motionControlledSprinkler(8); // Back Right
            break;
          }
        }
      }
      else
      {
        // Reset if motion stops
        motionStartTimes[i] = 0;
        motionAlreadyCounted[i] = false;
      }
    }
  }

  // Reset motion count after 1 hour
  if (motionCountExceeded && currentTime - lastMotionTime >= 3600000)
  {
    motionCount = 0;
    motionCountExceeded = false;
  }
}