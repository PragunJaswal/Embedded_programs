
int sensorPin = A0;
int ledPin = 13;     
int sensorValue = 0;  
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
 Serial.println(sensorValue);
 delay(100);

}
