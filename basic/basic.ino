#include <SoftwareSerial.h> //serial communication
SoftwareSerial MyBlue(2, 3); // RX | TX
int flag = 0; 
int LED = 8; 
void setup() 
{
 Serial.begin(9600); 
 MyBlue.begin(9600); 
 pinMode(LED, OUTPUT); 
 Serial.println("Ready to connect\n Defualt password is 1234 or 000"); 
}
void loop() {
Serial.println(MyBlue.read());
}
