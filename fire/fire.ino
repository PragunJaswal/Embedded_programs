void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
}

void loop()
{

if(digitalRead(13)==1){
  
  digitalWrite(12,LOW);
  }
else{
  digitalWrite(12,HIGH);
  }
}
