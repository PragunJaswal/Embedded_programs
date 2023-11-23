#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,1); //rx,tx
#define led 13
char data;
void setup(){
  pinMode(led,OUTPUT);
  
  Serial.begin(9600);
  mySerial.begin(9600);
  }
void loop(){
  
  if(mySerial.available()==1){
    
    data=mySerial.read();
    
    if(data=="A"){
    digitalWrite(led,HIGH);
      }
    if(data=="a"){
      digitalWrite(led,LOW);
      }
    
    }
    }
