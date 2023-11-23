
#include <SoftwareSerial.h>

const int rxPin = 0;
const int txPin = 1; 
SoftwareSerial bt(rxPin, txPin);
const int Loads[] = {6};
int state = 0;
int flag = 0;
void setup() 
{
for (int i=0;i<1;i++)
{
pinMode(Loads[i], OUTPUT);
}
bt.begin(9600);
for (int i=0;i<1;i++)
{digitalWrite(Loads[i], LOW);
}}





void loop() 


{
if(bt.available() > 0)


{
state = bt.read();
flag=0;
}
switch(state)
{
case '0':digitalWrite(Loads[0], HIGH);
flag=1;
break;
case '1':digitalWrite(Loads[0], LOW);
flag=1;
break;
case '2':digitalWrite(Loads[0], LOW);
digitalWrite(Loads[1], LOW);
digitalWrite(Loads[2], LOW);
digitalWrite(Loads[3], LOW);
flag=1;
break;}
}
