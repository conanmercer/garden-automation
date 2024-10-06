#ifndef CONSTANTS_H
#define CONSTANTS_H

// Solenoid Valve Pins
const int SOLENOID_VALVE_PINS[] = {4, 5, 13, 14, 16, 18, 34, 12, 15};
const int NUM_SOLENOID_VALVES = sizeof(SOLENOID_VALVE_PINS) / sizeof(SOLENOID_VALVE_PINS[0]);

// PIR Sensor Pins
const int PIR_SENSOR_PINS[] = {27, 26, 25}; // Left, Middle, Right
const int NUM_PIR_SENSORS = sizeof(PIR_SENSOR_PINS) / sizeof(PIR_SENSOR_PINS[0]);

// Lights Pins
const int LIGHT_PINS[] = {33, 32, 21};
const int NUM_LIGHTS = sizeof(LIGHT_PINS) / sizeof(LIGHT_PINS[0]);

// Constants for Water Cycles
// const unsigned long irrigationInterval = 24 * 60 * 60 * 1000; // 24 hours in milliseconds (summer)
const unsigned long irrigationInterval = 7 * 24 * 60 * 60 * 1000; // 7 days in milliseconds (winter)
// const unsigned long irrigationInterval = 10 * 1000;           // 10 seconds in milliseconds (testing)

// Lights Intervals
const unsigned long lightsIntervalOn = 1 * 60 * 60 * 1000UL;   // 1 hours in milliseconds
const unsigned long lightsIntervalOff = 23 * 60 * 60 * 1000UL; // 23 hours in milliseconds

#endif // CONSTANTS_H