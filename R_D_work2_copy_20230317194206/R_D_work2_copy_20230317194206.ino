#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include "DHTesp.h"  // Click here to get the library: http://librarymanager/All#DHTesp
#include <OneWire.h>
#include <DS18B20.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#define RLOAD 22.0
#include "MQ135.h"

const char* ssid = "Anonymous";
const char* password = "987654312";

const char* host = "tame-erin-gorilla-yoke.cyclic.app";
const int httpsPort = 443;


DS18B20 ds(15);  //pin of Water temp sensor


#define DS18B20MODEL 0x28
#define ONE_WIRE_BUS 15  //water sesnor pin
#define sensorPin 33     //mq135 pin
#define motorsense 35    //motor +ve pin and -ve will connect to ground
#define dhtPin 17        //dht22 pin
#define pHPin 34         //ph sensor pin
MQ135 gasSensor = MQ135(sensorPin);

int val;
int sensorValue = 0;
// Setup a oneWire instance to communicate with any OneWire devices that is DS18B20 sensor pin

// Pass our oneWire reference to Dallas Temperature sensor
#define LED 2
DHTesp dht;
BH1750 lightMeter;

float calibration_value = 16.15 + 00.22;  //calibrated value for ph sensor
float calibration_value2 = 00.72;         //calibrated value for water temperature sensor
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;
unsigned long previousMillis = 0;
unsigned long interval = 30000;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize the I2C bus
  dht.setup(dhtPin, DHTesp::DHT22);
  Serial.println("DHT initiated");
  pinMode(LED, OUTPUT);

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  pinMode(sensorPin, INPUT);
  pinMode(motorsense, INPUT);
  Serial.print("Devices: ");
  Serial.println(ds.getNumberOfDevices());
  Serial.println();
  // if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
  //   Serial.println(F("BH1750 Advanced begin"));
  // } else {
  //   Serial.println(F("Error initialising BH1750"));
  // }
  // Serial.println(F("BH1750 Test begin"));
  digitalWrite(LED, HIGH);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  digitalWrite(LED, LOW);
  delay(70);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(70);
  digitalWrite(LED, LOW);
  delay(70);
}



void loop() {

    unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }

  Serial.println("Started");
  WiFiClientSecure client;
  client.setInsecure();
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }
  delay(1000);
  int motor;
  int data = digitalRead(motorsense);
  if (data == 0) {
    motor = 0;
  } else {
    motor = 1;
  }
  Serial.print("Motor status ");
  Serial.println(motor);

  // code to avg the value of Light sensor
  int count = 10;
  int raw_light = 0;
  for (int i = 0; i < count; i++) {
    float lux = lightsensor();
    raw_light += lux;
    delay(50);
  }
  raw_light = raw_light / count;
  float final_lux = raw_light;
  Serial.print("Light: ");
  Serial.print(final_lux);
  Serial.println(" lx");

  // code to avg the value of Temperature and Humidity of Air

  count = 10;
  int raw_temp = 0;
  int raw_hum = 0;
  for (int i = 0; i < count; i++) {
    float temp = temp_air();
    raw_temp += temp;
    delay(50);
  }
  for (int i = 0; i < count; i++) {
    float hum = hum_air();
    raw_hum += hum;
    delay(50);
  }
  raw_temp = raw_temp / count;
  float final_temp = raw_temp;
  raw_hum = raw_hum / count;
  float final_hum = raw_hum;

  Serial.print("Temp of air : ");
  Serial.print(final_temp);
  Serial.println(" C");
  Serial.print("Humidity of air : ");
  Serial.print(final_hum);
  Serial.println(" %");

  // code to avg the value of Temperature of water
  float tempw = tempwat() + calibration_value2;
  Serial.print("Water Temp  ");
  Serial.print(tempw);
  Serial.println(" C");

  // code to avg the value of water pH
  for (int i = 0; i < 10; i++) {
    analogReadResolution(12);
    buffer_arr[i] = map(analogRead(pHPin), 0, 4096, 4096, 0);
    // Serial.println(buffer_arr[i]);
    delay(30);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 3.3 / 4096.0 / 6;
  //Serial.print("Voltage: ");
  //Serial.println(volt);
  // float calibration_value = mapf(analogRead(Pin), 0, 4096, 16.00, 27.12);
  // Serial.print("Cal value");
  // Serial.println(calibration_value);

  float ph_act = -5.70 * volt + calibration_value;

  Serial.print("pH Val: ");
  Serial.println(ph_act);
  delay(200);

  //                                     code to avg the co2 value of air
  count = 10;
  int raw_co2 = 0;
  for (int i = 0; i < count; i++) {
    float co2 = co();
    // Serial.println(co());
    raw_co2 += co2;
    delay(50);
  }
  raw_co2 = raw_co2 / count;
  float final_co2 = raw_co2;
  Serial.print("co2  ");
  Serial.print(final_co2);
  Serial.println(" ppm");

  //Upload the values to API
  String httpRequestData = "MotorStatus=" + String(motor) + "&LightIntensity=" + String(final_lux) + "&TempAir=" + String(final_temp) + "&HumAir=" + String(final_hum) + "&TempWater=" + String(tempw) + "&pH=" + String(ph_act) + "&co2Air=" + String(final_co2);
  String url = "https://tame-erin-gorilla-yoke.cyclic.app/api/v1/carbondata";

  client.print(String("POST ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: ESP32\r\n" + "Content-Type: application/x-www-form-urlencoded" + "\r\n" + "Content-Length: 98" + "\r\n\r\n" + httpRequestData + "\r\n" + "Connection: close\r\n\r\n");

  Serial.println(httpRequestData);
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

  Serial.println("Ended");
  delay(886000);
}







/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/

float lightsensor() {
  float lux = lightMeter.readLightLevel();
  // Serial.println(".");  // for debugging purpose
  return lux;
}

float temp_air() {

  TempAndHumidity newValues = dht.getTempAndHumidity();
  if (dht.getStatus() != 0) {
    Serial.println("DHT11 error status: " + String(dht.getStatusString()));
  }
  float temp = newValues.temperature;
  float humd = newValues.humidity;
  // Serial.println(" T:" + String(temp) + " H:" + String(humd)); // for debugging purpose
  return temp;
}
float hum_air() {

  TempAndHumidity newValues = dht.getTempAndHumidity();
  delay(50);
  if (dht.getStatus() != 0) {
    delay(200);
    Serial.println("DHT11 error status: " + String(dht.getStatusString()));
    digitalWrite(LED, HIGH);
    Serial.println("Reconnect the dht sesnor");
    delay(200);
    digitalWrite(LED, LOW);
    hum_air();
  }
  float temp = newValues.temperature;
  float humd = newValues.humidity;
  // Serial.println(" T:" + String(temp) + " H:" + String(humd)); // for debugging purpose
  return humd;
}

float tempwat() {
  float temp = ds.getTempC();
  return temp;
}
float co() {
  analogReadResolution(10);
  int val = analogRead(sensorPin);
  // Serial.println(val);
  //   float zero = gasSensor.getRZero();
  //   Serial.print ("rzero: ");
  //   Serial.println (zero);
  float ppm = gasSensor.getPPM();
  // Serial.println(ppm);
  return ppm;
}