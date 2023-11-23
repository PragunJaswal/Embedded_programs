#define ir 9
int data=0;
void setup(){
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  pinMode(ir,INPUT);
  }

 void loop(){
data = digitalRead(ir);

if(data==1){
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  }

if(data==0){
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  delay(1000);
  
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  delay(1000);
  }
  
  }
