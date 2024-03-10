#ifndef SOLENOIDS_H
#define SOLENOIDS_H

#include "constants.h"

// Function declarations
void turnOffAllSolenoidValves();
void turnOnSolenoidValve(int valveIndex);
void turnOffSolenoidValve(int valveIndex);
void motionControlledSprinkler(int valveIndex);

#endif // SOLENOIDS_H
