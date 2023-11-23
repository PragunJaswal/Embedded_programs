
int num;

void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);  
  pinMode(2,OUTPUT);
  pinMode(7,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(8)==0){
digitalWrite(6,HIGH);
digitalWrite(5,LOW);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
digitalWrite(2,HIGH);
digitalWrite(7,LOW);
}
else{
digitalWrite(7,HIGH);
digitalWrite(2,LOW);
  num =random(0,2);
digitalWrite(6,LOW);
digitalWrite(5,LOW);
digitalWrite(4,LOW);
digitalWrite(3,LOW);
delay(100);
digitalWrite(6,LOW);
digitalWrite(5,HIGH);
digitalWrite(4,LOW);
digitalWrite(3,HIGH);
delay(1000);
if(num==0){
digitalWrite(6,HIGH);
digitalWrite(5,LOW);
digitalWrite(4,LOW);
digitalWrite(3,LOW);
delay(1000);
}
else{
digitalWrite(6,LOW);
digitalWrite(5,LOW);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
delay(1000);


}
}

}
