#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include<SoftwareSerial.h>
SoftwareSerial BTserial(0,1);

#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define pirPin 8  
#define DHTPIN 2  
#define sensorPin 6 
#define rainPin 5
#define relay 9
int motion=0;
int bin =0;
int bin2 =0;
                   
                   //connect soil mositure to A0
                   //connect mq135 to         A1
int pirValue;
int pinValue;   
int sensorValue;
int sensorValue2;
int sensorState = 0;
int rainState = 0;
int lastState = 0;
int lastRainState = 0;
int sensor=0;
int sensor2=0;
int Incoming_value;
float temp;
float h;
float t;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void setup()
{
   Serial.begin(9600);
   BTserial.begin(9600);
   pinMode(sensorPin, INPUT);
   pinMode(rainPin, INPUT);
   pinMode(pirPin, INPUT);
   pinMode(relay, OUTPUT);
   pinMode(13, OUTPUT);
   dht.begin();
   sensors.begin();
}



void sendTemps()
{
sensor=analogRead(A0);
bin=map(sensor, 1024, 0, 0,100);                   //soil moisture data by A0
sensors.requestTemperatures();
temp = sensors.getTempCByIndex(A0); 
//if(sensor>700){
//  digitalWrite(relay,HIGH);
//  }
//if(sensor<400){
//  digitalWrite(relay,LOW);
//  }
// else {
//  digitalWrite(relay,HIGH);
//  }
delay(500);
}


void loop()
{
  //timer.run(); 
  sendTemps();
  h = dht.readHumidity();                //data from dht 11 from pin 2
  t = dht.readTemperature();
  
  sensorState = digitalRead(sensorPin);
                                                
  sensorValue = analogRead(A1); 
                                  // Data from mq135 from pin A1
                                  
  sensor2=analogRead(A2);
  bin2=map(sensor2, 1024, 0, 0,100); 
  sensorValue = analogRead(A3);
  if (sensorState == 1 && lastState == 0) {
                                              //    Serial.println("needs water, send notification");
    lastState = 1;
    delay(500);
    
//send notification   
  } 
  else if (sensorState == 1 && lastState == 1) {
                                             //do nothing, has not been watered yet
//  Serial.println("has not been watered yet");
  delay(500);
  }
  else {
    
//    Serial.println("does not need water");
    lastState = 0;
    delay(500);
  }



rainState = digitalRead(rainPin);                   //data from rain sensor
//Serial.println(rainState);

  if (rainState == 0 && lastRainState == 0) {
//  Serial.println("Its Raining!");
  lastRainState = 1;
  delay(500);
//send notification
    
  } 
  else if (rainState == 0 && lastRainState == 1) {
  delay(500);
  }
  else {
//    Serial.println("No Rains");
    lastRainState = 0;
    delay(500);
  }


 pirValue = digitalRead(pirPin);
     if (pirValue) 
     { 
       motion=0;
     }
     else{
      motion=1;
      }

  delay(100);
senddata();
}

void senddata(){
                                //  Serial.print("soil moisture = ");
  Serial.print(bin);
  Serial.print(",");
//  Serial.println(sensorState);
                            //  Serial.print(" soil moisture2  ");
  Serial.print(bin2);
  Serial.print(",");
  
  
                                //  Serial.print("AirQua= ");
  Serial.print(sensorValue, DEC);   
  Serial.print(",");           
//  Serial.println(" PPM");

                              //  Serial.print("air quality 2 ");
Serial.print(sensorValue2, DEC);   
  Serial.print(",");


                                  //  Serial.print("humidity= ");
  Serial.print(h);
                                //  Serial.print(",  temp.= ");
  Serial.print(",");
  Serial.print(t);
    
  Serial.print(";");
  
if (BTserial.available() > 0)
    { 
      Serial.print("\n");
      Incoming_value = Serial.read();
//      Serial.print(Incoming_value);
      
      if (Incoming_value == '1')
        {digitalWrite(relay,HIGH);
        Serial.print("relay on");
        Serial.print("\n");
    }
      else if(Incoming_value == '0')
       {digitalWrite(relay,LOW);
        Serial.print("relay off");
        Serial.print("\n");
    }}
  
  }
