#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"
#include "pin_initializer.h"

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
unsigned long previousMillis = 0;

// Motion
const unsigned long minMotionDuration = 2000;         // 2 seconds
unsigned long motionStartTimes[3] = {0, 0, 0};        // Track when motion started per PIR sensor
bool motionAlreadyCounted[3] = {false, false, false}; // prevent double-counting during continuous motion

void setup()
{
  Serial.begin(115200);

  // Initialize scheduler
  scheduler = Scheduler(irrigationInterval);
  scheduler.setIrrigationInterval(irrigationInterval);

  // Initialize pin configurations
  pinInitializer.setupSolenoidValvePins();
  pinInitializer.setupPIRSensorPins();
  pinInitializer.setupLightPins();

  // Initialize garden lights
  for (int i = 0; i < NUM_LIGHTS; i++)
  {
    digitalWrite(LIGHT_PINS[i], HIGH); // Turn on lights initially
  }

  unsigned long currentTime = millis();
  lightsAreOn = true;
  previousMillis = currentTime;

  nextOffTime = currentTime + lightsIntervalOn;           // Lights turn off in 3 hours
  nextOnTime = currentTime + irrigationInterval - 2000UL; // Next lights-on cycle before next irrigation

  scheduler.setLastIrrigationRun(millis() - irrigationInterval); // force scheduler to run irrigation immediately
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run(currentTime);

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
    // Turn lights on
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
      digitalWrite(LIGHT_PINS[i], HIGH);
    }
    lightsAreOn = true;
    previousMillis = currentTime;
    nextOffTime = currentTime + lightsIntervalOn;

    // Update next light cycle to happen 2 seconds before next irrigation
    nextOnTime = currentTime + irrigationInterval - 2000UL;
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

  // Check if 1 hour has passed since motion count exceeded 20
  if (motionCountExceeded && currentTime - lastMotionTime >= 3600000)
  {
    motionCount = 0;
    motionCountExceeded = false;
  }
}