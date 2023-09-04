#include <Arduino.h>

// Right PIR Sensor
const int PIR_SENSOR_OUTPUT_PIN_1 = 25;
// Middle PIR Sensor
const int PIR_SENSOR_OUTPUT_PIN_2 = 26;
// Left PIR Sensor
const int PIR_SENSOR_OUTPUT_PIN_3 = 27;

/* Solenoid valve connected to GPIO pin 4 connected to Relay pin IN_1 */
/* Solenoid valve connected to GPIO pin 5 connected to Relay pin IN_2 */
/* Solenoid valve connected to GPIO pin 13 connected to Relay pin IN_3 */
/* Solenoid valve connected to GPIO pin 14 connected to Relay pin IN_4 */
/* Solenoid valve connected to GPIO pin 16 connected to Relay pin IN_5 */

// Side Garden Water = pin 1
// Terrace Water = pin 2
// Right Sprinkler Water = pin 3
// Middle Sprinkler = pin 4

const int SOLENOID_VALVE_OUTPUT_PINS[] = {4, 5, 13, 14, 16};
const int NUM_SOLENOID_VALVES = sizeof(SOLENOID_VALVE_OUTPUT_PINS) / sizeof(SOLENOID_VALVE_OUTPUT_PINS[0]);

int warm_up;

void setup()
{
  Serial.begin(115200);

  // Loop through the SOLENOID_VALVE_OUTPUT_PINS array and set each pin as an output
  for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
  {
    pinMode(SOLENOID_VALVE_OUTPUT_PINS[i], OUTPUT);
  }

  // When the PIR senses activity in it's viewing area
  // it pulls the alarm pin HIGH. But when the sensor is inactive, the pin is basically floating.
  // INPUT_PULLDOWN makes sure no false positives
  pinMode(PIR_SENSOR_OUTPUT_PIN_1, INPUT_PULLDOWN);
  pinMode(PIR_SENSOR_OUTPUT_PIN_2, INPUT_PULLDOWN);
  pinMode(PIR_SENSOR_OUTPUT_PIN_3, INPUT_PULLDOWN);

  delay(20000);
}

void turnOffAllSolenoidValves()
{
  for (int i = 0; i < NUM_SOLENOID_VALVES; i++)
  {
    digitalWrite(SOLENOID_VALVE_OUTPUT_PINS[i], LOW);
    delay(100);
  }
}

void turnOnSolenoidValve(int valveIndex)
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PINS[valveIndex], HIGH);
}

void turnOffSolenoidValve(int valveIndex)
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PINS[valveIndex], LOW);
}

void cycleThroughAllValves()
{
  turnOffAllSolenoidValves();

  delay(100);

  turnOnSolenoidValve(0); // Mains water supply
  delay(100);

  for (int i = 1; i < NUM_SOLENOID_VALVES; i++)
  {
    turnOnSolenoidValve(i);
    delay(10000);
    turnOffSolenoidValve(i);
  }

  delay(100);
}

void turnOnRightSprinkler()
{
  turnOffAllSolenoidValves();

  delay(100);

  turnOnSolenoidValve(3);
  delay(500);
  turnOnSolenoidValve(0);
  delay(10000);
  turnOffSolenoidValve(3);
  // Allow 5 seconds for sprinkler to go back into ground otherwise motion detected
  delay(5000);
}

void turnOnMiddleSprinkler()
{
  turnOffAllSolenoidValves();

  turnOnSolenoidValve(4);
  delay(500);
  turnOnSolenoidValve(0);
  delay(10000);
  turnOffSolenoidValve(4);
  // Allow 5 seconds for sprinkler to go back into ground otherwise motion detected
  delay(5000);
}

void loop()
{
  int left_sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN_3);
  int middle_sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN_2);
  int right_sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN_1);

  if (left_sensor_output == HIGH)
  {
    turnOnMiddleSprinkler();
  }
  else if (middle_sensor_output == HIGH || right_sensor_output == HIGH)
  {
    turnOnRightSprinkler();
  }
  else
  {
    turnOffAllSolenoidValves();
  }
}
