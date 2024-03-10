#include "irrigation.h"
#include "solenoids.h"

void runIrrigation()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(2);
    unsigned long terraceDelay = random(60, 121) * 1000; // Generate random delay between 60 and 120 seconds
    delay(terraceDelay);                                 // Terrace random delay between 60 and 120 seconds
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(1);
    unsigned long sideGardenDelay = random(9, 12) * 60 * 1000; // Generate random delay between 9 and 11 minutes
    delay(sideGardenDelay);                                    // Side garden random between 9 and 11 minutes
    turnOffAllSolenoidValves();
}

void runSprinklers()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(3);
    unsigned long sprinklerDelay = random(9, 12) * 60 * 1000; // Generate random delay between 9 and 11 minutes
    delay(sprinklerDelay);                                    // Right Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(4);
    delay(sprinklerDelay); // Middle Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
}