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

  lightsAreOn = true;
  previousMillis = millis();
  nextOffTime = previousMillis + lightsIntervalOn; // Schedule the first turn-off time
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run(currentTime);

  // Manage the 2-hour on and 22-hour off cycle for garden lights
  if (lightsAreOn && (currentTime >= nextOffTime))
  {
    // Turn lights off
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
      digitalWrite(LIGHT_PINS[i], LOW);
    }
    lightsAreOn = false;
    previousMillis = currentTime;
    nextOnTime = currentTime + lightsIntervalOff - 60 * 1000UL; // Schedule next turn-on time 1 minute earlier
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
  }

  // Check PIR sensor pins for motion
  if (!motionCountExceeded)
  {
    // Check PIR sensor pins for motion
    for (int i = 0; i < 3; i++)
    {
      if (digitalRead(PIR_SENSOR_PINS[i]) == HIGH)
      {
        motionDetected = true;
        motionCount++;

        if (!motionCountExceeded && motionCount > 20)
        {
          motionCountExceeded = true;
          lastMotionTime = currentTime;
        }
      }
    }
  }

  // Process motion detection
  if (motionDetected)
  {
    if (!motionCountExceeded)
    {
      // Within the allowed limit
      if (digitalRead(PIR_SENSOR_PINS[0]) == HIGH)
      {
        motionControlledSprinkler(4); // Middle Sprinkler
      }
      else
      {
        motionControlledSprinkler(3); // Right Sprinkler
        motionControlledSprinkler(8); // Back Right Sprinkler
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