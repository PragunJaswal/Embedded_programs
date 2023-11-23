#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Anonymous";
const char* password = "987654312";

#define BTN_PIN 5
#define TFT_DC 2
#define TFT_CS 15

const String url = "https://v2.jokeapi.dev/joke/Programming";

String getJoke() {
  HTTPClient http;
  http.useHTTP10(true);
  http.begin(url);
  http.GET();
  String result = http.getString();

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, result);

  // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return "<error>";
  }

  String type = doc["type"].as<String>();
  String joke = doc["joke"].as<String>();
  String setup = doc["setup"].as<String>();
  String delivery = doc["delivery"].as<String>();
  http.end();
  return type.equals("single") ? joke : setup + "  " + delivery;
}

void nextJoke() {


  Serial.print("Joke loading ");

  String joke = getJoke();

  Serial.println(joke);
}

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
Serial.begin(9600);
  WiFi.begin(ssid, password, 6);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }


Serial.println(WiFi.localIP());
  nextJoke();
}

void loop() {
    nextJoke();
  
  delay(10000);
}