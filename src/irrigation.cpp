#include "irrigation.h"
#include "solenoids.h"

void runIrrigation()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(2);
    unsigned long terraceDelay = random(60, 90) * 1000; // Generate random delay between 60 and 90 seconds
    delay(terraceDelay);                                // Terrace random delay between 60 and 90 seconds
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(1);
    unsigned long sideGardenDelay = random(13, 15) * 60 * 1000; // Generate random delay between 5 and 10 minutes
    delay(sideGardenDelay);                                     // Side garden random between 5 and 10 minutes
    turnOffAllSolenoidValves();
}

void runSprinklers()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(3);
    unsigned long sprinklerDelay = random(13, 15) * 60 * 1000; // Generate random delay between 5 and 10 minutes
    delay(sprinklerDelay);                                     // Right Sprinkler random between 5 and 10 minutes
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(4);
    delay(sprinklerDelay); // Middle Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(5);
    delay(sprinklerDelay); // Left Sprinkler random between 9 and 11 minutes
    turnOffAllSolenoidValves();
}