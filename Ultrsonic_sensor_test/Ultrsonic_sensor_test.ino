#include <SoftwareSerial.h> 
 
SoftwareSerial mySerial (2, 3);    


#define motor1 4
#define motor2 5
#define motor3 6
#define motor4 7
#define noob   8



void setup()
{
   
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(noob, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  

  
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(13));
if(digitalRead(13)==1){
  
  digitalWrite(12,LOW);
  }
else{
  digitalWrite(12,HIGH);
  }

  
  if(mySerial.available() == 1)   
  {
    char val = mySerial.read();   
    Serial.println("Recieved data is " + (String) val);
    if(val == 'B')    
    {
      
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
      
    }
    if(val == 'F')
    {
      
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, HIGH);
      
    }
    if(val == 'R')
    {
     
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
      
    }
    if(val == 'L')
    {
      
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, HIGH);
      
    }
    if(val == 'l')
    {
    
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
      
    }
    if(val == 'r')
    {
      
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
      
    }
    if(val == 'm')
    {
     
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, HIGH);
    }
    if(val == 'n')
    {
     
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
    }
   
    if(val == 'Y')
    {
      
      digitalWrite(noob, HIGH);
\
    }
    if(val == 'y')
    {
     
      digitalWrite(noob, LOW);

    }
    if(val == 'S')
    {
      
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
      
    }
  }
}
