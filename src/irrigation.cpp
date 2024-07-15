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
    unsigned long gardenDelay = random(13, 15) * 60 * 1000; // Generate random delay between 13 and 15 minutes
    delay(gardenDelay);                                     // Side Garden lower
    // turnOffAllSolenoidValves();
    // turnOnSolenoidValve(0);
    // turnOnSolenoidValve(6);
    // delay(gardenDelay); // Side Garden
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(7);
    delay(gardenDelay); // Top Garden
    turnOffAllSolenoidValves();
}

void runSprinklers()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(3);
    unsigned long sprinklerDelay = random(13, 15) * 60 * 1000; // Generate random delay between 13 and 15 minutes
    delay(sprinklerDelay);                                     // Right Sprinkler
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(8);
    delay(sprinklerDelay); // Back Right Sprinkler
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(4);
    delay(sprinklerDelay); // Middle Sprinkler
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(5);
    delay(sprinklerDelay); // Left Sprinkler
    turnOffAllSolenoidValves();
}