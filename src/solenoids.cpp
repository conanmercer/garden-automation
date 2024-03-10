#include <Arduino.h>
#include "solenoids.h"

/**
 * Function to turn off all
 * solenoid valves
 */
void turnOffAllSolenoidValves()
{
    for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
    {
        digitalWrite(SOLENOID_VALVE_PINS[i], LOW);
        delay(100);
    }
}

/**
 * Function to turn on specific
 * solenoid valves
 */
void turnOnSolenoidValve(int valveIndex)
{
    digitalWrite(SOLENOID_VALVE_PINS[valveIndex], HIGH);
}

/**
 * Function to turn off specific
 * solenoid valves
 */
void turnOffSolenoidValve(int valveIndex)
{
    digitalWrite(SOLENOID_VALVE_PINS[valveIndex], LOW);
}

/**
 * Function to turn on specific
 * solenoid valve if motion detected
 */
void motionControlledSprinkler(int valveIndex)
{
    turnOffAllSolenoidValves();
    turnOnSolenoidValve(valveIndex);
    delay(500);
    turnOnSolenoidValve(0); // Main supply valve
    delay(10000);
    turnOffSolenoidValve(valveIndex);
    delay(5000);
    turnOffAllSolenoidValves();
}