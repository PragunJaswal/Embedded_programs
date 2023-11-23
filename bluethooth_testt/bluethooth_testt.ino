#include <SoftwareSerial.h> //serial communication
SoftwareSerial blue(2, 3); // RX | TX
int LED  = 8;
char data;
void setup() 
{   
 Serial.begin(9600); 
 blue.begin(9600); 
 pinMode(LED, OUTPUT); 
 Serial.println("Ready to connect");
}
void loop() 
{
if(blue.available()==1)

{
  data = blue.read();
  Serial.println(data);
}}
