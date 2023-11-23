#include <SoftwareSerial.h>
SoftwareSerial bluetooth(D2, D3); // RX, TX
char t;

#define MLa D5 //left motor 1st pin

#define MLb D6//left motor 2nd pin

#define MRa D7 //right motor 1st pin

#define MRb D9 //right motor 2nd pin


void setup()
{
Serial.begin(9600);

bluetooth.begin(9600);

pinMode(MLa,OUTPUT); //left motors forward
pinMode(MLb,OUTPUT); //left motors reverse
pinMode(MRa,OUTPUT); //right motors forward pinMode(MRb, OUTPUT); //right motors reverse
pinMode(MRb,OUTPUT);
Serial.println("Started");
}

void loop()

{

if(bluetooth.available()>0)
{
t = bluetooth.read();

Serial.println(t);

}

switch(t)
{
case 'F': {            //move forward(all motors rotate in forward direction)

digitalWrite(MLa,HIGH);

digitalWrite(MLb,LOW);

digitalWrite(MRa,HIGH);

digitalWrite(MRb,LOW);

}

break;

case 'B': {//move reverse (all motors rotate in reverse direction)

digitalWrite(MLa,LOW);

digitalWrite(MLb,HIGH);

digitalWrite(MRa,LOW); digitalWrite(MRb,HIGH);

}

break;
case 'L': {//turn right (left side motors rotate in forward direction, right side motors doesn't rotate)

digitalWrite(MLa,LOW);

digitalWrite(MLb,LOW);

digitalWrite(MRa,HIGH);

digitalWrite(MRb,LOW);

}

break;

case 'R': {//turn left (right side motors rotate in forward direction, left side motors doesn't rotate)


digitalWrite(MLa,HIGH);
digitalWrite(MLb,LOW);
digitalWrite(MRa,LOW);

digitalWrite(MRb,LOW);

}

break;

case 'S': {//STOP (all motors stop)

digitalWrite(MLa,LOW);

digitalWrite(MLb,LOW);

digitalWrite(MRa,LOW);

digitalWrite(MRb,LOW);

}

}
}
