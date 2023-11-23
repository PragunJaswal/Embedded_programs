#define RLOAD 22.0
#include "MQ135.h"

MQ135 gasSensor = MQ135(12);
int val;
int sensorPin = 33;
int sensorValue = 0;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}
void loop() {
  analogReadResolution(10);
  val = analogRead(33);
  Serial.print ("raw = ");
  Serial.println (val);
 float zero = gasSensor.getRZero();
 Serial.print ("rzero: ");
  Serial.println (zero);
  float ppm = gasSensor.getPPM();
  Serial.print ("ppm: ");
  Serial.println (ppm);

  delay(1000);
}