void setup() {

 pinMode(6, OUTPUT);
  pinMode(7, INPUT);
}

void loop() {

if (6 == HIGH)
 {
  digitalWrite(6, HIGH);
}
else
{
 digitalWrite(6,LOW);
}
}
