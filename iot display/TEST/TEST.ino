#include <ESP8266WebServer.h>
#include <DMDESP.h>
#include <fonts/EMSansSP8x16.h>
#include <fonts/ElektronMart6x12.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "Your_SSID";          // Change to your Wi-Fi SSID
const char* password = "Your_Password";  // Change to your Wi-Fi password
String data;
int fail = 0;

// ----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 4                     //--> Panel Columns
#define DISPLAYS_HIGH 1                     //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)

// ----------------------------------------
const int textWidth = 8 * 11;
const int displayWidth = 128;  // Width of your display in pixels
bool dataFetched = false;      // Flag to track if data has been fetched
String Show_Data = "";

// Define states
enum State {
  SCROLL_TEXT,
  SHOW_YEAR,
  SHOW_NEWS,
};

// Initialize state
State currentState;
unsigned long stateStartTime;

void setup() {
  Serial.begin(115200);
  delay(500);

  EEPROM.begin(512);
  delay(500);

  // ----------------------------------------DMDESP Setup
  Disp.start();                    //--> Run the DMDESP library
  Disp.setBrightness(50);          //--> Brightness level
  Disp.setFont(ElektronMart6x12);  //--> Determine the font used
  // ----------------------------------------

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  unsigned long wifiStartTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStartTime < 10000) {
    Serial.print('.');
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    // Continue with the rest of your setup
  } else {
    Serial.println("\nFailed to connect to WiFi");
    // Handle the case where Wi-Fi connection fails, e.g., retry or take appropriate action
    // ESP.restart();
    Disp.drawText(8, 0, ";(  503");
    delay(1500);
  }

  // Initialize state and state start time
  currentState = SCROLL_TEXT;
  stateStartTime = millis();
}

void loop() {
  Disp.loop();
  unsigned long currentTime = millis();

  switch (currentState) {
    case SCROLL_TEXT:
      scrollText("WELCOME TO DEPTT. OF ELECTRONICS and COMMUNICATION ENGG.");
      if (currentTime - stateStartTime >= 10000) {  // Display for 10 seconds
        // Switch to SHOW_YEAR state
        currentState = SHOW_YEAR;
        stateStartTime = currentTime;
        Disp.clear();
      }
      break;
    case SHOW_YEAR:
      showYear();
      if (currentTime - stateStartTime >= 10000) {  // Display for 10 seconds
        // Switch to SHOW_NEWS state
        currentState = SHOW_NEWS;
        stateStartTime = currentTime;
        Disp.clear();
      }
      break;

    case SHOW_NEWS:
      showNews();
      if (currentTime - stateStartTime >= 10000) {  // Display for 10 seconds
        // Repeat the cycle by switching back to SCROLL_TEXT state
        currentState = SCROLL_TEXT;
        stateStartTime = currentTime;
        Disp.clear();
      }
      break;
  }
}

void scrollText(const char* text) {
  int y = 0;
  int scrolling_speed = 10;
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(EMSansSP8x16);
  int fullScroll = Disp.textWidth(text) + width;

  if ((millis() - pM) > scrolling_speed) {
    pM = millis();

    if (x < fullScroll) {
      ++x;
      // Add fade-in effect for the first 50 pixels
      int fadeLength = 50;
      if (x < fadeLength) {
        byte brightness = map(x, 0, fadeLength, 0, 255);
        // Set text intensity (brightness)
        Disp.setBrightness(brightness);
      } else {
        // Set full brightness once the fade-in is complete
        Disp.setBrightness(255);
      }
    } else {
      // Switch to the SHOW_YEAR state
      currentState = SHOW_YEAR;
      stateStartTime = millis();
      x = 0;
      // Reset text intensity (brightness)
      Disp.setBrightness(255);
      // Reset the dataFetched flag when switching to SHOW_YEAR state
      dataFetched = false;
    }
    Disp.drawText(width - x, y, text);
  }
}

void showYear() {
  // ... (existing show year code)
}

void showNews() {
  // ... (existing show news code)
}
