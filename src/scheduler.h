// Scheduler class handles scheduling of irrigation
// and sprinkler operations based on predefined intervals

#include <Arduino.h>
#include "solenoids.h"
#include "irrigation.h"
#include "constants.h"

class Scheduler
{
private:
    unsigned long lastIrrigationRun = 0;
    unsigned long lastSprinklersRun = 0;
    unsigned long irrigationInterval;
    unsigned long sprinklersInterval;

public:
    // Constructor for Scheduler class
    // Initializes the irrigation and sprinklers intervals
    Scheduler(unsigned long irrigationInterval, unsigned long sprinklersInterval) : irrigationInterval(irrigationInterval),
                                                                                    sprinklersInterval(sprinklersInterval) {}

    void run(unsigned long currentTime)
    {
        if (currentTime - lastIrrigationRun >= irrigationInterval)
        {
            runIrrigation();
            Serial.println("Irrigation completed.");
            lastIrrigationRun = currentTime;
        }

        else if (currentTime - lastSprinklersRun >= sprinklersInterval)
        {
            runSprinklers();
            Serial.println("Sprinkler completed.");
            lastSprinklersRun = currentTime;
        }
    }

    void setIrrigationInterval(unsigned long interval)
    {
        irrigationInterval = interval;
    }

    void setSprinklersInterval(unsigned long interval)
    {
        sprinklersInterval = interval;
    }
};