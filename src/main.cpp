#include <Arduino.h>

const int PIR_SENSOR_OUTPUT_PIN = 26; /* PIR sensor O/P pin */

const int SOLENOID_VALVE_OUTPUT_PIN_1 = 4;  /* Solenoid valve connected to GPIO pin 4 connected to Relay pin IN_1 */
const int SOLENOID_VALVE_OUTPUT_PIN_2 = 5;  /* Solenoid valve connected to GPIO pin 5 connected to Relay pin IN_2 */
const int SOLENOID_VALVE_OUTPUT_PIN_3 = 13; /* Solenoid valve connected to GPIO pin 13 connected to Relay pin IN_3 */
const int SOLENOID_VALVE_OUTPUT_PIN_4 = 14; /* Solenoid valve connected to GPIO pin 14 connected to Relay pin IN_4 */
const int SOLENOID_VALVE_OUTPUT_PIN_5 = 16; /* Solenoid valve connected to GPIO pin 16 connected to Relay pin IN_5 */

int warm_up;

void setup()
{
  // Solenoid Pins
  pinMode(SOLENOID_VALVE_OUTPUT_PIN_1, OUTPUT);
  pinMode(SOLENOID_VALVE_OUTPUT_PIN_2, OUTPUT);
  pinMode(SOLENOID_VALVE_OUTPUT_PIN_3, OUTPUT);
  pinMode(SOLENOID_VALVE_OUTPUT_PIN_4, OUTPUT);
  pinMode(SOLENOID_VALVE_OUTPUT_PIN_5, OUTPUT);

  // PIR PINS
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
}

void turnOffAllSolenoidValves()
{
  // Turn off each solenoid valve with 100ms second delays between each actuation
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_1, LOW);
  delay(100); // Delay
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_2, LOW);
  delay(100); // Delay
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_3, LOW);
  delay(100); // Delay
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_4, LOW);
  delay(100); // Delay
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_5, LOW);
  delay(100); // Delay
}

void turnOnMainsSolenoidValve()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_1, HIGH);
}

void turnOffMainsSolenoidValve()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_1, LOW);
}

void turnOnSolenoidValve2()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_2, HIGH);
}

void turnOnSolenoidValve3()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_3, HIGH);
}

void turnOnSolenoidValve4()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_4, HIGH);
}

void turnOnSolenoidValve5()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_5, HIGH);
}

void turnOffSolenoidValve2()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_2, LOW);
}

void turnOffSolenoidValve3()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_3, LOW);
}

void turnOffSolenoidValve4()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_4, LOW);
}

void turnOffSolenoidValve5()
{
  digitalWrite(SOLENOID_VALVE_OUTPUT_PIN_5, LOW);
}

void controlSolenoidValve()
{

  turnOffAllSolenoidValves();

  delay(1000);

  turnOnMainsSolenoidValve();
  delay(100); // Delay
  turnOnSolenoidValve2();

  delay(10000);
  turnOffSolenoidValve2();
  turnOnSolenoidValve3();

  delay(10000);
  turnOffSolenoidValve3();
  turnOnSolenoidValve4();

  delay(10000);
  turnOffSolenoidValve4();
  turnOnSolenoidValve5();

  delay(10000);
}

void testPIRSolenoidValve()
{

  turnOffAllSolenoidValves();

  delay(100);

  turnOnMainsSolenoidValve();
  delay(100); // Delay

  turnOnSolenoidValve3();
  delay(10000);
  turnOffSolenoidValve3();
}

void testPIR()
{
  int sensor_output;
  sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
  if (sensor_output == LOW)
  {
  }
  else
  {
    testPIRSolenoidValve();
  }
}

void loop()
{
  // Solenoid CODE BELOW

  // delay(1000); // Delay
  // controlSolenoidValve();
  // delay(1000); // Delay

  // PIR CODE BELOW

  testPIR();
}