void setup() {
Serial.begin(9600);
pinMode(13,INPUT);
digitalWrite(13,1);
Serial.println(1);
delay(1000);
digitalWrite(13,0);
delay(1000);
  

}

void loop() {

}
