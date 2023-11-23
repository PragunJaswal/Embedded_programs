#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>


const char* ssid = "Anonymous";
const char* password = "987654312";
  
WiFiMulti wifiMulti;
 
void setup() {
  Serial.begin(9600);
   
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}
 

void loop() {
  // Not used in this example
   postDataToServer();
   delay(5000);
}
 
void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  // Block until we are able to connect to the WiFi access point
  if (WiFi.status()  == WL_CONNECTED) {
     Serial.println("Started");
    HTTPClient http;   
     
    http.begin("https://script.google.com/macros/s/AKfycbxK8ixvoLHP_fkRAeKy3cSOwZI-kMqSFM_lScLHAg3hmSfsdGoO_A49qmQbvIMj1q52/exec?action=adduser");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    doc["busid"] = "praguntest";
    doc["latitude"] = "20.36121560";
    doc["longitude"] = "76.51824120";
   
    // Add an array.
    //
    // JsonArray data = doc.createNestedArray("data");
    // data.add(48.756080);
    // data.add(2.302038);
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
    Serial.println(requestBody);
    Serial.println("data posted");
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
    else {
     
      Serial.println("Error occurred while sending HTTP POST: ");
       
    }
     
  }
}