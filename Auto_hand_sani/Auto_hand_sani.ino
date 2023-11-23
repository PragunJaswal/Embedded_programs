void setup() {
pinMode(5,INPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
Serial.begin(9600);
}

void loop() {
int dataa =  digitalRead(5);
Serial.println(dataa);

if(dataa==0){
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  delay(2000);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  
  }
 else{
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  
  }

}
