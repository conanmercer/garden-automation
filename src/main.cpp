#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"
#include "pin_initializer.h"

unsigned long lastMotionTime = 0; // Timestamp of the last motion detected
int motionCount = 0;              // Counter for motion detections
bool motionCountExceeded = false; // Flag to track if motion count exceeded

// Constants for water cycles
const unsigned long irrigationInterval = 25 * 60 * 60 * 1000; // 25 hours in milliseconds
// const unsigned long irrigationInterval = 10 * 1000;           // 10 seconds in milliseconds (testing)
const unsigned long sprinklersInterval = 10 * 60 * 60 * 1000; // 10 hours in milliseconds
// const unsigned long sprinklersInterval = 10 * 1000; // 10 seconds in milliseconds (testing)

Scheduler scheduler(irrigationInterval, sprinklersInterval);
PinInitializer pinInitializer;

// Constants for garden light cycles
const int gardenLightPins[] = {33, 32, 21}; // Pins for garden lights
const int numGardenLights = sizeof(gardenLightPins) / sizeof(gardenLightPins[0]);
const unsigned long intervalHigh = 2UL * 60 * 60 * 1000; // 2 hours in milliseconds
const unsigned long intervalLow = 22UL * 60 * 60 * 1000; // 22 hours in milliseconds
unsigned long previousMillis = 0;                        // Store the last time the lights were updated
bool lightsAreOn = true;

void setup()
{
  Serial.begin(115200);
  // Initialize scheduler
  scheduler = Scheduler(irrigationInterval, sprinklersInterval);
  scheduler.setIrrigationInterval(irrigationInterval);
  scheduler.setSprinklersInterval(sprinklersInterval);

  // Initialize pin configuration
  pinInitializer.setupSolenoidValvePins();
  pinInitializer.setupPIRSensorPins();

  // Initialize random number generator with a seed
  randomSeed(analogRead(0));

  // Initialize garden lights
  for (int i = 0; i < numGardenLights; i++)
  {
    pinMode(gardenLightPins[i], OUTPUT);
    digitalWrite(gardenLightPins[i], HIGH); // Turn on lights initially
  }
  previousMillis = millis();
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run(currentTime);

  // Manage the 2-hour on and 22-hour off cycle for garden lights
  if ((currentTime - previousMillis >= (lightsAreOn ? intervalHigh : intervalLow)))
  {
    // Toggle lights state
    for (int i = 0; i < numGardenLights; i++)
    {
      digitalWrite(gardenLightPins[i], lightsAreOn ? LOW : HIGH);
    }
    lightsAreOn = !lightsAreOn;
    previousMillis = currentTime;
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