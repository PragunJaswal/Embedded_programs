#include <ESP8266WiFi.h>

const char* ssid = "Anonymou";
const char* password = "987654312";

unsigned long previous_time = 0;
unsigned long delay1 = 5000;  // 5 seconds delay

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI network");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(17,LOW);
    digitalWrite(18,LOW);
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  initWiFi();
}

void loop() {
  unsigned long current_time = millis(); // number of milliseconds since the upload

  // checking for WIFI connection
  if ((WiFi.status() != WL_CONNECTED) && (current_time-previous_time >=delay1)) {
    Serial.println(millis());
    digitalWrite(17,LOW);
    digitalWrite(18,LOW);
    Serial.println("Reconnecting to WIFI network");
    WiFi.disconnect();
    WiFi.reconnect();
    previous_time = current_time;
  }
  while(WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi Connected");
    digitalWrite(17,HIGH);
    int sense;
    sense =analogRead(A0);
    Serial.println(sense);  // get value using T0
    delay(100);
    if (sense < 30){
      digitalWrite(18,HIGH);
    }
    else{digitalWrite(18,LOW);
    }

  }
}