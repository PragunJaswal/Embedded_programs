#include <WiFi.h>
#include <esp_task_wdt.h>
#include "soc/rtc_wdt.h"



const char* ssid = "Anonymou";
const char* password = "987654312";
hw_timer_t* timer = NULL;

unsigned long previous_time = 0;
unsigned long delay1 = 8;  // 5 seconds delay
#define led2 27            //green
#define led1 25            //red
#define button 14
int connected = false;
volatile int ledState = LOW;
volatile unsigned long lastMillis = 0;
unsigned long previousMillis = 0;

void setup() {
 
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  unsigned long current_time = 0;
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  Serial.print("Connecting to WIFI network");
  while (WiFi.status() != WL_CONNECTED and (current_time < delay1)) {

    Serial.print('.');
    current_time = current_time + 1;
    // Serial.print(current_time);
    // Serial.print(current_time <delay1);
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    connected = true;
  } else {
    connected = false;
    Serial.print("WiFi Not Connected ");
    WiFi.disconnect();
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(200);
    esp_deep_sleep_start();
  }
  timer = timerBegin(0, 80, true);

  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);

  /* Set alarm to call onTimer function every second 1 tick is 1us
  => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 5000000, true);

  /* Start an alarm */
  timerAlarmEnable(timer);
}

void onTimer() {

  if (digitalRead(button) == LOW) {
    ESP.restart();
  }

  if ((WiFi.status() == WL_CONNECTED)) {
    Serial.print("WiFi Connected :: ");
    Serial.println(WiFi.localIP());
    int sense;
    sense = touchRead(T0);
    if (sense < 30) {
      Serial.println("Touch Detected");
      const long interval = 100;  // interval at which to blink (milliseconds)
      bool ledState = false;

  for (int i = 0; i < 2; i++) { // blink the LED twice
    ledState = !ledState;
    digitalWrite(led1, ledState ? HIGH : LOW);
    unsigned long startMillis = millis();
    while (millis() - startMillis < interval) {
      // wait for the interval to elapse
    }
  }

  digitalWrite(led1, HIGH); // turn off the LED after blinking
  for (int i = 0; i < 2; i++) { // blink the LED twice
    ledState = !ledState;
    digitalWrite(led1, ledState ? HIGH : LOW);
    unsigned long startMillis = millis();
    while (millis() - startMillis < interval) {
      // wait for the interval to elapse
    }
  }
  digitalWrite(led1, HIGH);
    } else {
      Serial.println("Touch Not Detected");
      digitalWrite(led1, LOW);
      delay(100);
      digitalWrite(led1, HIGH);
      delay(200);
      digitalWrite(led2, LOW);
      delay(100);
      digitalWrite(led2, HIGH);
      delay(200);
    }
  } else {
    Serial.print("WiFi Disconnected ");
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(200);
    esp_deep_sleep_start();
  }

}

void loop(){

}