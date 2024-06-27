#ifndef CONSTANTS_H
#define CONSTANTS_H

// Solenoid Valve Pins
const int SOLENOID_VALVE_PINS[] = {4, 5, 13, 14, 16, 18};
const int NUM_SOLENOID_VALVES = sizeof(SOLENOID_VALVE_PINS) / sizeof(SOLENOID_VALVE_PINS[0]);
// PIR Sensor Pins
const int PIR_SENSOR_PINS[] = {27, 26, 25}; // Left, Middle, Right
const int NUM_PIR_SENSORS = sizeof(PIR_SENSOR_PINS) / sizeof(PIR_SENSOR_PINS[0]);

#endif // CONSTANTS_H