// Scheduler class handles scheduling of irrigation
// operations based on predefined intervals

#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "constants.h"

class Scheduler
{
private:
    unsigned long lastIrrigationRun = 0;
    unsigned long irrigationInterval;

public:
    // Constructor for Scheduler class
    // Initializes the irrigation intervals
    Scheduler(unsigned long irrigationInterval) : irrigationInterval(irrigationInterval) {}

    void run(unsigned long currentTime)
    {
        if (currentTime - lastIrrigationRun >= irrigationInterval)
        {
            runIrrigation();
            Serial.println("Irrigation completed.");
            lastIrrigationRun = currentTime;
        }
    }

    void setIrrigationInterval(unsigned long interval)
    {
        irrigationInterval = interval;
    }
};