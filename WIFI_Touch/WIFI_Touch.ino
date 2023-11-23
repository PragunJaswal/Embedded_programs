#include <WiFi.h>

const char* ssid = "Anonymou";
const char* password = "987654312";

unsigned long previous_time = 0;
unsigned long delay1 = 5000;  // 5 seconds delay25
#define led1 27  //red
#define led2 25  //green
#define button 14

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI network");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  initWiFi();
}

void loop() {
  unsigned long current_time = millis(); // number of milliseconds since the upload

  // checking for WIFI connection
  if ((WiFi.status() != WL_CONNECTED) && (current_time-previous_time >=delay1)) {
    Serial.println(millis());
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    Serial.println("Reconnecting to WIFI network");
    WiFi.disconnect();
    WiFi.reconnect();
    previous_time = current_time;
  }
  while(WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi Connected");
    int sense;
    sense =touchRead(T0);
    Serial.println(sense);  // get value using T0
    delay(100);
    if (sense < 30){
      Serial.println("Touch detected");
      Serial.println(digitalRead(button));
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
    }
    else{
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    }
  }
}