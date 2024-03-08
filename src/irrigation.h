#include <Arduino.h>
#include "solenoids.h"

void runIrrigation()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(2);
    unsigned long delayTime = random(60, 121) * 1000; // Generate random delay between 60 and 120 seconds
    delay(delayTime);                                 // Terrace random delay between 60 and 120 seconds
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(1);
    unsigned long delayTime = random(9, 12) * 60 * 1000; // Generate random delay between 9 and 11 minutes
    delay(delayTime);                                    // Side garden random between 9 and 11 minutes
    turnOffAllSolenoidValves();
}

void runSprinklers()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(3);
    unsigned long delayTime = random(9, 12) * 60 * 1000; // Generate random delay between 9 and 11 minutes
    delay(delayTime);                                    // Right Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(4);
    delay(delayTime); // Middle Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
}
