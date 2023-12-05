#include <Arduino.h>
#include <unity.h>
#include "solenoids.h"

void setupSolenoidValvePins()
{
    for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
    {
        pinMode(SOLENOID_VALVE_PINS[i], OUTPUT);
    }
}

void setUp(void)
{
    setupSolenoidValvePins();
}

void tearDown(void)
{
    // clean stuff up here
}

void test_turnOffAllSolenoidValves(void)
{
    // Arrange: Turn on all solenoid valves
    for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
    {
        digitalWrite(SOLENOID_VALVE_PINS[i], HIGH);
        delay(100);
    }

    // Act: Call the function to turn off all solenoid valves
    turnOffAllSolenoidValves();

    // Assert: Verify if all solenoid valves are turned off
    for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
    {
        TEST_ASSERT_EQUAL_INT(LOW, digitalRead(SOLENOID_VALVE_PINS[i]));
    }
}

void test_turnOnSolenoidValve(void)
{
    // Arrange: Turn off all solenoid valves
    for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
    {
        digitalWrite(SOLENOID_VALVE_PINS[i], LOW);
        delay(100);
    }

    // Act: Call the function to turn on solenoid valve
    turnOnSolenoidValve(2);

    // Assert: Verify if solenoid valve is turned on
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(SOLENOID_VALVE_PINS[2]));
}

void setup()
{
    delay(2000);   // service delay
    UNITY_BEGIN(); // start unit testing

    RUN_TEST(test_turnOffAllSolenoidValves);
    RUN_TEST(test_turnOnSolenoidValve);

    UNITY_END(); // stop unit testing
}

void loop()
{
}