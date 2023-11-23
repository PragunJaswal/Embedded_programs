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


const char* ssid = "Anonymous";
const char* password = "987654312";
String data;
int fail = 0;
///----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 4                     //--> Panel Columns
#define DISPLAYS_HIGH 1                     //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)
//----------------------------------------
const int textWidth = 8 * 11;  // Width of the text "JNGEC - 0 2 9" in pixels
const int displayWidth = 128;  // Width of your display in pixels
bool dataFetched = false;      // Flag to track if data has been fetched

void setup() {
  Serial.begin(115200);
  delay(500);

  EEPROM.begin(512);
  delay(500);

  //----------------------------------------DMDESP Setup
  Disp.start();                    //--> Run the DMDESP library
  Disp.setBrightness(50);          //--> Brightness level
  Disp.setFont(ElektronMart6x12);  //--> Determine the font used
  //----------------------------------------
  //Connect to Wi-Fi
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
}

// Define states
enum State {
  SCROLL_TEXT,
  SHOW_YEAR,
  SHOW_NEWS,
};

// Initialize state
State currentState = SCROLL_TEXT;
unsigned long stateStartTime;

void scroll() {
  int y = 0;
  int scrolling_speed = 10;
  char* Text[] = { "WELCOME TO DEPTT. OF ELECTRONICS and COMMUNICATION ENGG." };
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(EMSansSP8x16);
  int fullScroll = Disp.textWidth(Text[0]) + width;

  if ((millis() - pM) > scrolling_speed) {
    pM = millis();

    switch (currentState) {
      case SCROLL_TEXT:
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
        Disp.drawText(width - x, y, Text[0]);
        break;

      case SHOW_YEAR:
        if (!dataFetched) {  // Fetch data only once when switching to SHOW_YEAR state
          if ((WiFi.status() == WL_CONNECTED)) {
            std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

            // Ignore SSL certificate validation
            client->setInsecure();

            //create an HTTPClient instance
            HTTPClient https;

            //Initializing an HTTPS communication using the secure client
            Serial.print("[HTTPS] begin...\n");
            if (https.begin(*client, "https://worldtimeapi.org/api/timezone/Asia/Kolkata")) {  // HTTPS
              Serial.print("[HTTPS] GET...\n");
              // start connection and send HTTP header
              int httpCode = https.GET();
              // httpCode will be negative on error
              if (httpCode > 0) {
                // HTTP header has been sent and Server response header has been handled
                Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                // file found at server
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                  String payload = https.getString();
                  // Serial.println(payload);
                  StaticJsonDocument<768> doc;
                  DeserializationError error = deserializeJson(doc, payload);
                  if (error) {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.f_str());
                  } else {
                    const char* datetime = doc["datetime"];
                    Serial.print("Date time: ");
                    Serial.println(datetime);

                    String datetimeString = String(datetime);  // Convert to a String

                    int dateStart = datetimeString.indexOf("") + 5;  // Start of date
                    int timeStart = dateStart + 6;                   // Start of time (HH:MM)

                    // Extract date and time
                    String date = datetimeString.substring(dateStart, dateStart + 5);  // 10 characters for the date
                    String time = datetimeString.substring(timeStart, timeStart + 5);  // 5 characters for HH:MM

                    Serial.println("Date: " + date);
                    Serial.println("Time: " + time);
                    data = String(time) + "  " + String(date);
                  }
                }
              } else {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
                fail += 1;
              }

              https.end();
              dataFetched = true;  // Set the flag to true after data is fetched
            } else {
              fail += 1;
              Serial.printf("[HTTPS] Unable to connect\n");
            }
          } else {
            // Switch back to the SCROLL_TEXT state after 10 seconds
            currentState = SCROLL_TEXT;
            // Clear the display
            Disp.drawText(8, y, ";(  503");
            delay(1500);
            Disp.clear();
            break;
          }
        }
        if (fail == 2) {
          fail = 0;
          Disp.drawText(12, y, ";(  503");
          delay(1500);
          ESP.restart();
        }

        // Display the date and time
        Disp.drawText(12, y, String(data));

        if (millis() - stateStartTime >= 10000) {  // Display for 10 seconds
          // Switch back to the SCROLL_TEXT state after 10 seconds
          currentState = SHOW_NEWS;
          // Clear the display
          Disp.clear();
        }
        break;
      case SHOW_NEWS:
        if ((WiFi.status() == WL_CONNECTED)) {
          std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

          // Ignore SSL certificate validation
          client->setInsecure();

          //create an HTTPClient instance
          HTTPClient https;

          //Initializing an HTTPS communication using the secure client
          Serial.print("[HTTPS] begin...\n");
          if (https.begin(*client, "https://news-api-vaqm.onrender.com/toggle")) {  // HTTPS
            Serial.print("[HTTPS] GET...\n");
            // start connection and send HTTP header
            int httpCode = https.GET();
            // httpCode will be negative on error
            if (httpCode > 0) {
              // HTTP header has been sent and Server response header has been handled
              Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
              // file found at server
              if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                String payload = https.getString();
                Serial.println(payload);
                StaticJsonDocument<50> doc;
                DeserializationError error = deserializeJson(doc, payload);
                if (error) {
                  Serial.print(F("deserializeJson() failed: "));
                  Serial.println(error.f_str());
                } else {
                  bool state = doc["state"];
                  Serial.print("State ");
                  Serial.println(state);

                  if (state == 0) {
                    if ((WiFi.status() == WL_CONNECTED)) {
                      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

                      // Ignore SSL certificate validation
                      client->setInsecure();

                      //create an HTTPClient instance
                      HTTPClient https;

                      //Initializing an HTTPS communication using the secure client
                      Serial.print("[HTTPS] begin...\n");
                      if (https.begin(*client, "https://news-api-vaqm.onrender.com/news-top")) {  // HTTPS
                        Serial.print("[HTTPS] GET...\n");
                        // start connection and send HTTP header
                        int httpCode = https.GET();
                        // httpCode will be negative on error
                        if (httpCode > 0) {
                          // HTTP header has been sent and Server response header has been handled
                          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                          // file found at server
                          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                            String payload = https.getString();
                            // Serial.println(payload);
                            StaticJsonDocument<768> doc;
                            DeserializationError error = deserializeJson(doc, payload);
                            if (error) {
                              Serial.print(F("deserializeJson() failed: "));
                              Serial.println(error.f_str());
                            } else {
                              String news = doc["title"];
                              Serial.print("title ");
                              Serial.println(news);
                            }
                          }
                        } else {
                          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
                          fail += 1;
                        }

                        https.end();
                        dataFetched = true;  // Set the flag to true after data is fetched
                      } else {
                        fail += 1;
                        Serial.printf("[HTTPS] Unable to connect\n");
                      }
                    }
                  } else {
                    if ((WiFi.status() == WL_CONNECTED)) {
                      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

                      // Ignore SSL certificate validation
                      client->setInsecure();

                      //create an HTTPClient instance
                      HTTPClient https;

                      //Initializing an HTTPS communication using the secure client
                      Serial.print("[HTTPS] begin...\n");
                      if (https.begin(*client, "https://news-api-vaqm.onrender.com/get/notice")) {  // HTTPS
                        Serial.print("[HTTPS] GET...\n");
                        // start connection and send HTTP header
                        int httpCode = https.GET();
                        // httpCode will be negative on error
                        if (httpCode > 0) {
                          // HTTP header has been sent and Server response header has been handled
                          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                          // file found at server
                          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                            String payload = https.getString();
                            // Serial.println(payload);
                            StaticJsonDocument<768> doc;
                            DeserializationError error = deserializeJson(doc, payload);
                            if (error) {
                              Serial.print(F("deserializeJson() failed: "));
                              Serial.println(error.f_str());
                            } else {
                              String news = doc["title"];
                              Serial.print("title ");
                              Serial.println(news);
                            }
                          }
                        } else {
                          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
                          fail += 1;
                        }

                        https.end();
                        dataFetched = true;  // Set the flag to true after data is fetched
                      } else {
                        fail += 1;
                        Serial.printf("[HTTPS] Unable to connect\n");
                      }
                    }
                  }
                }
              } else {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
                fail += 1;
              }

              https.end();
            } else {
              fail += 1;
              Serial.printf("[HTTPS] Unable to connect\n");
            }
          } else {
            // Switch back to the SCROLL_TEXT state after 10 seconds
            currentState = SCROLL_TEXT;
            // Clear the display
            Disp.drawText(8, y, ";(  503");
            delay(1500);
            Disp.clear();
            break;
          }

          if (fail == 2) {
            fail = 0;
            Disp.drawText(12, y, ";(  503");
            delay(1500);
            ESP.restart();
          }

          // Display the date and time
          Disp.drawText(12, y, String(data));

          if (millis() - stateStartTime >= 10000) {  // Display for 10 seconds
            // Switch back to the SCROLL_TEXT state after 10 seconds
            currentState = SCROLL_TEXT;
            // Clear the display
            Disp.clear();
          }
          break;
        }
    }
  }
}

  void loop() {
    Disp.loop();
    scroll();
  }