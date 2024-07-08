#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "scheduler.h"
#include "pin_initializer.h"

unsigned long lastMotionTime = 0; // Timestamp of the last motion detected
int motionCount = 0;              // Counter for motion detections
bool motionCountExceeded = false; // Flag to track if motion count exceeded

const unsigned long irrigationInterval = 1 * 24 * 60 * 60 * 1000; // 1.5 days in milliseconds (summer)
const unsigned long sprinklersInterval = 12 * 60 * 60 * 1000;     // 12 hours in milliseconds

Scheduler scheduler(irrigationInterval, sprinklersInterval);
PinInitializer pinInitializer;

// Constants for garden light cycle
const int gardenLightPin1 = 33;                          // Pin for garden light 1
const int gardenLightPin2 = 32;                          // Pin for garden light 2
const unsigned long intervalHigh = 3UL * 60 * 60 * 1000; // 3 hours in milliseconds
const unsigned long intervalLow = 21UL * 60 * 60 * 1000; // 21 hours in milliseconds
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
  pinMode(gardenLightPin1, OUTPUT);
  pinMode(gardenLightPin2, OUTPUT);
  digitalWrite(gardenLightPin1, HIGH);
  digitalWrite(gardenLightPin2, HIGH);
  previousMillis = millis();
}

void loop()
{
  unsigned long currentTime = millis();
  bool motionDetected = false;

  scheduler.run(currentTime);

  // Manage the 3-hour on and 21-hour off cycle for garden lights
  if (lightsAreOn && (currentTime - previousMillis >= intervalHigh))
  {
    // Turn lights off
    digitalWrite(gardenLightPin1, LOW);
    digitalWrite(gardenLightPin2, LOW);
    lightsAreOn = false;
    previousMillis = currentTime;
  }
  else if (!lightsAreOn && (currentTime - previousMillis >= intervalLow))
  {
    // Turn lights on
    digitalWrite(gardenLightPin1, HIGH);
    digitalWrite(gardenLightPin2, HIGH);
    lightsAreOn = true;
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