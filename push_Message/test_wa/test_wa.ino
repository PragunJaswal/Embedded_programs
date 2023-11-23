#include <ESP8266WiFi.h>
#include <ThingESP.h>

ThingESP8266 thing("punisher", "ESP8266", "1234567890");

int LED = D2;

unsigned long previousMillis = 0;
const long INTERVAL = 6000;  

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(D0, INPUT);
  thing.SetWiFi("Anonymous", "987654312");
  thing.initDevice();
}


String HandleResponse(String query)
{
//  if (query == "led on") {
//    digitalWrite(LED, 1);
//    return "Done: LED Turned ON";
//  }
//
//  else if (query == "led off") {
//    digitalWrite(LED, 0);
//    return "Done: LED Turned OFF";
//  }
//
//  else if (query == "led status")
//    return digitalRead(LED) ? "LED is OFF" : "LED is ON";
//  else return "Your query was invalid..";
//if (digitalRead(D0)==0){
//  return "Button pressed ";
//  }
//  else return "not pressed";
//  delay(1000);
}


void loop()
{
  thing.Handle();
  String msg = digitalRead(D0)?"Button not pressed" : "Button Pressed";
  thing.sendMsg("+918544722770",msg);
  delay(1000);
}
