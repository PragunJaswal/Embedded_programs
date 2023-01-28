/*
Hello this is pragun
*/
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
// Wi-Fi Credentials
const char* ssid = "Anonymous";
const char* password = "987654312";

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\nHELLO WORLD\n");
  setup_wifi();
}
void loop() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n\nPerforming HTTP GET Request\n");

    // HTTP Details
    String requestUrl = "https://brown-worm-hem.cyclic.app/";
    http.begin(client, requestUrl);
    //    http.setAuthorization("Basic token");
    //    http.setAuthorization("Bearer token");

    // Send HTTP GET request
    int httpResponseCode = http.GET();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Response payload: " + payload);

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();

      String value = obj[String("response")];
      Serial.println("\nresponse is : " + value);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(10000);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}