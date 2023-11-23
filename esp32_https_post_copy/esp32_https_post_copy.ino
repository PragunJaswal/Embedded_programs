#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "Anonymous";
const char* password = "987654312";

const char* host = "script.googleusercontent.com";
const int httpsPort = 443;

const char* fingerprint = "-----BEGIN CERTIFICATE-----"
"MIIFxjCCBK6gAwIBAgIQA2vaDTdUd5Lx+wG65E14ATANBgkqhkiG9w0BAQsFADA8"
"MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRwwGgYDVQQDExNBbWF6b24g"
"UlNBIDIwNDggTTAxMB4XDTIzMDIxMDAwMDAwMFoXDTIzMDkxNzIzNTk1OVowFzEV"
"MBMGA1UEAwwMKi5jeWNsaWMuYXBwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB"
"CgKCAQEAutwDpsAY1sk775A4RNRXY+o4+ssoJayU72TTqD8LHS9O7bXPaEIC3AL3"
"mpGjcIeAI8m5nuz3THT4IC7Pr/tsUYQb0/uBXhp+K6TqIsIT4SS8HWZNAPiDdl8x"
"fr59+4weKeE0jyp3HYA7sD41oeP3yCjti8Vjev5qaBKid6Ol585jwerIhuRQzhyj"
"//7DsiDZ1u9aLYek1neTTj1XJICZk7b48qyXexmJorVZj/g2/VvclNT6cuc70OvQ"
"siH8Lp+otrb7dosTNCStNgyD7ogcmvwdaRKc4leBUBe9Ft1BedETglzyPfkTPlLs"
"8ZNI5zUENbGyelH5SYQ6qdCVGKN7sQIDAQABo4IC5zCCAuMwHwYDVR0jBBgwFoAU"
"gbgOY4qJEhjl+js7UJWf5uWQE4UwHQYDVR0OBBYEFCnTpN0BYuQSKEjzW2ynxuSD"
"oc3vMBcGA1UdEQQQMA6CDCouY3ljbGljLmFwcDAOBgNVHQ8BAf8EBAMCBaAwHQYD"
"VR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMDsGA1UdHwQ0MDIwMKAuoCyGKmh0"
"dHA6Ly9jcmwucjJtMDEuYW1hem9udHJ1c3QuY29tL3IybTAxLmNybDATBgNVHSAE"
"DDAKMAgGBmeBDAECATB1BggrBgEFBQcBAQRpMGcwLQYIKwYBBQUHMAGGIWh0dHA6"
"Ly9vY3NwLnIybTAxLmFtYXpvbnRydXN0LmNvbTA2BggrBgEFBQcwAoYqaHR0cDov"
"L2NydC5yMm0wMS5hbWF6b250cnVzdC5jb20vcjJtMDEuY2VyMAwGA1UdEwEB/wQC"
"MAAwggGABgorBgEEAdZ5AgQCBIIBcASCAWwBagB3AOg+0No+9QY1MudXKLyJa8kD"
"08vREWvs62nhd31tBr1uAAABhjnBQXQAAAQDAEgwRgIhAOdPuTPakAgGjkA69IQc"
"ZW7Gyd0dUmSE3Gb9cOrOGFKwAiEA1TIeqH/LhbIJ5vISVy56VYE9RdDWdKWpRj5p"
"9ZigFjwAdgCzc3cH4YRQ+GOG1gWp3BEJSnktsWcMC4fc8AMOeTalmgAAAYY5wUFY"
"AAAEAwBHMEUCICKpyKo5hEjjZxG1iPB87s+k7ViirbHYKlm0N5zFsV0/AiEA4tRQ"
"ZVFkwoUUTy5wUmaSABUD7mgP42BovJg+dMLdQd4AdwC3Pvsk35xNunXyOcW6WPRs"
"XfxCz3qfNcSeHQmBJe20mQAAAYY5wUEoAAAEAwBIMEYCIQCtaS1VBjJVMKsrGhWJ"
"9Ffd05tMS1mVCoM2Aw2gw99XNQIhAOcZsDtGZqgVAlWE9QP2W/WrCe39q1B7w3zo"
"LZheDmJ4MA0GCSqGSIb3DQEBCwUAA4IBAQDUQA8ZTtbPZsZjXEx5cKc7RKweYSDK"
"SuSSkwVvkDyO4mjJTcLlaDk4eF+/4aePVaBaTVgQyNLZcE/LGDTX14k+7tQpw+uK"
"RrKOJT1YN9gErlutmoqsbKuAiLqj6Q3vqVKG2mlzwpDW6B8F9/w6hI9nBJ40fA7m"
"hbk2c0VSF4mEmWFG83nDhZ3m9II7hI30tMliScJMWgVC+kfoyaJ6SD8Jcaf9y+Qt"
"hMi8bE5EKlkTLJJxFwxtEkwCxVj9467vGtaNKhTXIIcfo9LMK6qdEIdLe+FDZsWL"
"h/6Izx4Zb+Gnp9/hw7wdNWvrmUgC0U1rVneGH8nKFU367NMC7RhaQGYs"
"-----END CERTIFICATE-----"; // SHA-1 fingerprint of the server certificate

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

void loop() {

  WiFiClientSecure client;
  // client.setCACert(fingerprint);
  client.setInsecure(); 
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }
int temp =10;
  String url = "https://script.google.com/macros/s/AKfycbwO-T9urjHyFmu1wPFIZ1Z1O-4JxMArPtUBm_n3_cS7B2qlD6tOop2g9i0Oxa6pC6PJ/exec?action=adduser";



// StaticJsonDocument<200> doc;
// doc["Latitude"] = "12.365445";
// doc["Longitude"] = 25.6;

// // Convert the JSON document to a string
// String jsonString;
// serializeJson(doc, jsonString);


//   String name = doc["Longitude"];
//   int age = doc["Latitude"];
//     Serial.println(name);
//   Serial.println(age);


   StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["Latitude"] = "gps";
    doc["Longitude"] = 1351824120;
   
    // Add an array.
    //
    JsonArray data = doc.createNestedArray("data");
    data.add(48.756080);
    data.add(2.302038);
     
    String requestBody;
    serializeJson(doc, requestBody);



  client.print(String("POST ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: ESP32\r\n" + "Content-Type: application/json" + "\r\n" + "Content-Length: 98" + "\r\n\r\n" + requestBody + "\r\n" + "Connection: close\r\n\r\n");

  Serial.println(requestBody);
  Serial.println("DATA POSTED");

  // Read the response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }

  String response = client.readString();
  Serial.println("Response received:");
  Serial.println(response);
  client.stop();

Serial.println("DATA POSTED");

  // Read the response

  delay(3000);




}