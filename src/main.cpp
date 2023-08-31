#include <Arduino.h>

const int PIR_SENSOR_OUTPUT_PIN_1 = 26;
const int PIR_SENSOR_OUTPUT_PIN_2 = 27;
const int PIR_SENSOR_OUTPUT_PIN_3 = 25;

/* Solenoid valve connected to GPIO pin 4 connected to Relay pin IN_1 */
/* Solenoid valve connected to GPIO pin 5 connected to Relay pin IN_2 */
/* Solenoid valve connected to GPIO pin 13 connected to Relay pin IN_3 */
/* Solenoid valve connected to GPIO pin 14 connected to Relay pin IN_4 */
/* Solenoid valve connected to GPIO pin 16 connected to Relay pin IN_5 */

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

  // Set the PIR sensor pins as inputs with pull-up resistors
  // When the PIR senses activity in it's viewing area
  // it pulls the alarm pin low. But when the sensor is inactive, the pin is basically floating.
  // To avoid any false-positives, the alarm output should be pulled high to 5V
  pinMode(PIR_SENSOR_OUTPUT_PIN_1, INPUT_PULLUP);
  pinMode(PIR_SENSOR_OUTPUT_PIN_2, INPUT_PULLUP);
  pinMode(PIR_SENSOR_OUTPUT_PIN_3, INPUT_PULLUP);

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

  turnOnSolenoidValve(0);
  turnOnSolenoidValve(2);
  delay(10000);
  turnOffSolenoidValve(2);
}

void turnOnMiddleSprinkler()
{
  turnOffAllSolenoidValves();

  delay(100);

  turnOnSolenoidValve(0);
  turnOnSolenoidValve(3);
  delay(10000);
  turnOffSolenoidValve(3);
}

void loop()
{
  int sensor_output_1 = digitalRead(PIR_SENSOR_OUTPUT_PIN_1);
  int sensor_output_2 = digitalRead(PIR_SENSOR_OUTPUT_PIN_2);

  int sensor_output_3 = digitalRead(PIR_SENSOR_OUTPUT_PIN_3);

  if (sensor_output_1 == LOW || sensor_output_2 == LOW)
  {
    if (warm_up == 1)
    {
      warm_up = 0;
      delay(2000);
    }
    delay(1000);
  }
  else
  {
    turnOnRightSprinkler();
    warm_up = 1;
    delay(1000);
  }

  if (sensor_output_3 == LOW)
  {
    if (warm_up == 1)
    {
      warm_up = 0;
      delay(2000);
    }
    delay(1000);
  }
  else
  {
    turnOnMiddleSprinkler();
    warm_up = 1;
    delay(1000);
  }
}
