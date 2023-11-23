int val = 0;

void setup() {
Serial.begin(9600);  


}

void loop() {

  val= analogRead(A0);
  Serial.println("Started");
Serial.println(analogRead(A0)/60);
Serial.println(analogRead(A1)/60);
Serial.println(analogRead(A2)/60);
Serial.println(analogRead(A3)/60);

}
