#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"

// PIR Sensor Pins
const int PIR_SENSOR_PINS[] = {27, 26, 25}; // Left, Middle, Right
const int NUM_PIR_SENSORS = sizeof(PIR_SENSOR_PINS) / sizeof(PIR_SENSOR_PINS[0]);

unsigned long lastMotionTime = 0; // Timestamp of the last motion detected
int motionCount = 0;              // Counter for motion detections
bool motionCountExceeded = false; // Flag to track if motion count exceeded

// const unsigned long irrigationInterval = 2UL * 24 * 60 * 60 * 1000; // 2 days in milliseconds (summer)
// const unsigned long sprinklersInterval = 24 * 60 * 60 * 1000;       // 1 day in milliseconds (summer)
const unsigned long irrigationInterval = 6UL * 24 * 60 * 60 * 1000; // 6 days in milliseconds (winter)
const unsigned long sprinklersInterval = 7UL * 24 * 60 * 60 * 1000; // 7 days in milliseconds (winter)
// const unsigned long irrigationInterval = 3UL * 1000; // 3 seconds in milliseconds (for testing)
// const unsigned long sprinklersInterval = 5UL * 1000; // 5 seconds in milliseconds (for testing)

Scheduler scheduler(irrigationInterval, sprinklersInterval);

void setup()
{
  scheduler = Scheduler(irrigationInterval, sprinklersInterval);
  scheduler.setIrrigationInterval(irrigationInterval);
  scheduler.setSprinklersInterval(sprinklersInterval);

  // Initialize Solenoid Valve Pins as OUTPUT
  for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
  {
    pinMode(SOLENOID_VALVE_PINS[i], OUTPUT);
  }

  // Initialize PIR Sensor Pins with INPUT_PULLDOWN
  for (int i = 0; i < NUM_PIR_SENSORS; i++)
  {
    pinMode(PIR_SENSOR_PINS[i], INPUT_PULLDOWN);
  }
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run();

  // the following is turned off for the moment:

  // Check PIR sensor pins for motion
  // Check if motionCountExceeded is false before running the loop
  // if (!motionCountExceeded)
  // {
  //   // Check PIR sensor pins for motion
  //   for (int i = 0; i < 3; i++)
  //   {
  //     if (digitalRead(PIR_SENSOR_PINS[i]) == HIGH)
  //     {
  //       motionDetected = true;
  //       motionCount++;

  //       if (!motionCountExceeded && motionCount > 5)
  //       {
  //         motionCountExceeded = true;
  //         lastMotionTime = currentTime;
  //       }
  //     }
  //   }
  // }

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