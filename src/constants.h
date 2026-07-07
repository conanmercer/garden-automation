#ifndef CONSTANTS_H
#define CONSTANTS_H

// Solenoid Valve Pins
const int SOLENOID_VALVE_PINS[] = {4, 5, 13, 14, 16, 18, 34, 12, 15, 22};
const int NUM_SOLENOID_VALVES = sizeof(SOLENOID_VALVE_PINS) / sizeof(SOLENOID_VALVE_PINS[0]);

// PIR Sensor Pins
const int PIR_SENSOR_PINS[] = {27, 26, 25}; // Left, Middle, Right
const int NUM_PIR_SENSORS = sizeof(PIR_SENSOR_PINS) / sizeof(PIR_SENSOR_PINS[0]);

// Temporarily disable lights from ever turning on
const bool LIGHTS_DISABLED = false;

// Lights Pins
const int LIGHT_PINS[] = {33, 32, 21, 17};
const int NUM_LIGHTS = sizeof(LIGHT_PINS) / sizeof(LIGHT_PINS[0]);

// Constants for Water Cycles
const unsigned long irrigationInterval = 1UL * 24UL * 60UL * 60UL * 1000UL; // 1 days in milliseconds (summer)
// const unsigned long irrigationInterval = 7UL * 24UL * 60UL * 60UL * 1000UL; // 1 week in milliseconds (winter)
const unsigned long initialIrrigationDelay = 7UL * 60UL * 60UL * 1000UL; // 7 hours after system boot
// const unsigned long initialIrrigationDelay = 3000UL; // 3 seconds after system boot

// Lights Intervals
const unsigned long lightsIntervalOn = 3 * 60 * 60 * 1000UL;     // 3 hours
const unsigned long lightsIntervalOff = 21 * 60 * 60 * 1000UL;   // 21 hours (24 - 3 = 21)
const unsigned long lightsCycleInterval = 24 * 60 * 60 * 1000UL; // 24 hours for daily light cycle

// Voltage Sensor Pin & Constants
const int VOLTAGE_SENSOR_PIN = 35;
const float R1 = 30000.0;
const float R2 = 7500.0;
const float VREF = 3.3;
const float VOLTAGE_CORRECTION = 11.34 / 10.51;

const float MIN_REQUIRED_VOLTAGE = 13.2;

#endif // CONSTANTS_H