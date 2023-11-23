void setup() {
pinMode(10,INPUT);
pinMode(9,OUTPUT);
Serial.begin(9600);
}

void loop() {
int dataa = digitalRead(10);
Serial.println(dataa);

if (dataa==0){
digitalWrite(9,HIGH);
Serial.println("LED IS ON");
}
else{
  digitalWrite(9,LOW);
  Serial.println("LED IS OFF");
  }
}
