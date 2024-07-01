#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"
#include "pin_initializer.h"

unsigned long lastMotionTime = 0; // Timestamp of the last motion detected
int motionCount = 0;              // Counter for motion detections
bool motionCountExceeded = false; // Flag to track if motion count exceeded

const unsigned long irrigationInterval = 1.5 * 24 * 60 * 60 * 1000; // 1.5 days in milliseconds (summer)
const unsigned long sprinklersInterval = 12 * 60 * 60 * 1000;       // 12 hours in milliseconds
// const unsigned long irrigationInterval = 6UL * 24 * 60 * 60 * 1000; // 6 days in milliseconds (winter)
// const unsigned long sprinklersInterval = 7UL * 24 * 60 * 60 * 1000; // 7 days in milliseconds (winter)
// const unsigned long irrigationInterval = 25UL * 60 * 1000; // 12 minutes in milliseconds (for testing)
// const unsigned long sprinklersInterval = 27UL * 60 * 1000; // 14 minutes in milliseconds (for testing)

Scheduler scheduler(irrigationInterval, sprinklersInterval);
PinInitializer pinInitializer;

void setup()
{
  Serial.begin(115200);
  // Initialize scheduler
  // Set the intervals for the scheduler
  scheduler = Scheduler(irrigationInterval, sprinklersInterval);
  scheduler.setIrrigationInterval(irrigationInterval);
  scheduler.setSprinklersInterval(sprinklersInterval);

  // Initialize pin configuration
  pinInitializer.setupSolenoidValvePins();
  pinInitializer.setupPIRSensorPins();

  // Initialize random number generator with a seed
  randomSeed(analogRead(0));
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run(currentTime);

  // the following is turned off for the moment:

  // Check PIR sensor pins for motion
  // Check if motionCountExceeded is false before running the loop
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
      }
    }
    else
    {
    }
  }

  // Check if 1 hour have passed since motion count exceeded 5
  if (motionCountExceeded && currentTime - lastMotionTime >= 3600000)
  {
    motionCount = 0;
    motionCountExceeded = false;
  }
}