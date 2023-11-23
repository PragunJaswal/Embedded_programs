void setup() {

  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  
  Serial.begin(9600);
}
  

void loop() {
  if(digitalRead(8)==1 and digitalRead(9)==1){
digitalWrite(5,HIGH);
digitalWrite(6,LOW);  
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
digitalWrite(2,HIGH);
digitalWrite(7,LOW);
}

  if(digitalRead(8)==0 and digitalRead(9)==1){
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
//digitalWrite(2,HIGH);
//digitalWrite(7,LOW);
}

  if(digitalRead(8)==1 and digitalRead(9)==0){
digitalWrite(5,HIGH);
digitalWrite(6,LOW);
digitalWrite(4,LOW);
digitalWrite(3,LOW);
//digitalWrite(2,HIGH);
//digitalWrite(7,LOW);
}



}