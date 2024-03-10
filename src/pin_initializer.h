// Pin initializer class handles pin initialization

#include <Arduino.h>
#include "constants.h"

class PinInitializer
{
public:
    PinInitializer() {}

    // Function to set up solenoid valve pins as OUTPUT
    void setupSolenoidValvePins()
    {
        for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
        {
            pinMode(SOLENOID_VALVE_PINS[i], OUTPUT);
        }
    }

    // Function to set up PIR sensor pins with INPUT_PULLDOWN
    void setupPIRSensorPins()
    {
        for (int i = 0; i < NUM_PIR_SENSORS; i++)
        {
            pinMode(PIR_SENSOR_PINS[i], INPUT_PULLDOWN);
        }
    }
};