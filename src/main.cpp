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
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
  Serial.begin(115200); // initialize serial
  Serial.println("Waiting For Power On Warm Up");
  delay(20000); /* Power On Warm Up Delay */
  Serial.println("Ready!");
}

void loop()
{
  int sensor_output;
  sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
  if (sensor_output == LOW)
  {
    if (warm_up == 1)
    {
      Serial.print("Warming Up\n\n");
      warm_up = 0;
      delay(2000);
    }
    Serial.print("No object in sight\n\n");
    delay(1000);
  }
  else
  {
    Serial.print("Object detected\n\n");
    warm_up = 1;
    delay(1000);
  }
}