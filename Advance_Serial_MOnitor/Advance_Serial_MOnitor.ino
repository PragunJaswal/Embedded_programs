char wordd=0;

void setup() {
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {

if(Serial.available() > 1)
{

wordd =Serial.read();
delay(1);
Serial.println(wordd);

if (wordd == "o"){
  digitalWrite(13,HIGH);
  Serial.println("LED is ON");
  }
else if(wordd == "f"){
  digitalWrite(13,LOW);
  Serial.println("LED is Off");
  }
}}
