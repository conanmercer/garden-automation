#include "irrigation.h"
#include "solenoids.h"

// Helper function to turn off all solenoid valves, turn on valve 0, and then turn on an additional valve
void activateSolenoids(int additionalValve)
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(additionalValve);
}

void runIrrigation()
{
    activateSolenoids(2);
    unsigned long terraceDelay = 45 * 1000; // Fixed delay of 90 seconds
    delay(terraceDelay);                    // Terrace random delay between 60 and 90 seconds

    activateSolenoids(1);
    unsigned long gardenDelay = 5 * 60 * 1000; // Fixed delay of 10 minutes
    delay(gardenDelay);                        // Side Garden lower

    // Uncomment and modify if needed
    // activateSolenoids(6);
    // delay(gardenDelay); // Side Garden

    activateSolenoids(7);
    delay(gardenDelay); // Top Garden

    turnOffAllSolenoidValves();

    // runSprinklers

    activateSolenoids(8);
    unsigned long sprinklerDelay = 14 * 60 * 1000; // Fixed delay of 14 minutes
    delay(sprinklerDelay);                         // Back Right Sprinkler

    activateSolenoids(3);
    delay(sprinklerDelay); // Right Sprinkler

    activateSolenoids(4);
    delay(sprinklerDelay); // Right Middle Sprinkler

    activateSolenoids(9);
    delay(sprinklerDelay); // Left Middle Sprinkler

    activateSolenoids(5);
    delay(sprinklerDelay); // Left Sprinkler

    turnOffAllSolenoidValves();
}