#include <Arduino.h>
#include "solenoids.h"

void runIrrigation()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(2);
    delay(90000); // Terrace 1.5 mins
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(1);
    delay(600000); // Side garden 10 mins
    turnOffAllSolenoidValves();
}

void runSprinklers()
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(3);
    delay(600000); // Right Sprinkler 10 mins
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(0);
    turnOnSolenoidValve(4);
    delay(600000); // Middle Sprinkler 10 mins
    turnOffAllSolenoidValves();
}
