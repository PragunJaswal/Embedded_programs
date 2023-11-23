#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
#define led1 4
#define led2 3
#define led3 5
int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
RF24 radio(9,10); // NRF24L01 SPI pins. Pin 9 and 10 on the Nano

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void)
{
  radio.begin(); // Start the NRF24L01

  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive

  radio.startListening(); // Listen to see if information received

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Started");
  while (radio.available()){
  Serial.println("available");
  
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01
Serial.print("ReceivedMessage  ");
Serial.println(ReceivedMessage[0]);
digitalWrite(led3, HIGH);
    if (ReceivedMessage[0] == 111) // Indicates switch is pressed
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      Serial.println("LOW");
    }
    else
    {
       digitalWrite(led1, HIGH);
       digitalWrite(led2, LOW);
       Serial.println("HIGH");
    }
    delay(2);
   }
while (radio.available()==0){
Serial.println("not connected");

digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
delay(100);
digitalWrite(led3,HIGH);
delay(700);
break;
}
}
