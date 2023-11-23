#define BLYNK_TEMPLATE_ID "TMPLSduf7GyG"
#define BLYNK_DEVICE_NAME "robo"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#include <DHT.h>
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 #include <Wire.h>
 #include <SPI.h>
 #include <Adafruit_Sensor.h>
 #include <Adafruit_BMP280.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#define APP_DEBUG
#define ENA D10
#define IN1 D7
#define IN2 D8
#define IN3 D0
#define IN4 D4
//#define ENB D4
#include "BlynkEdgent.h"
#define SEALEVELPRESSURE_HPA (1013.25)
 Adafruit_BMP280 bmp;
 float pressure, altitude;
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed=130;
int pos=0;
int data =0;
int sensorValue=0; 
#include <Servo.h>

Servo myservo;

void setup()
{
  Serial.begin(115200);
//Wire.begin();
//  bmp.begin(0x76); 
  delay(100);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
//  pinMode(ENB, OUTPUT);
  myservo.attach(D6); 
  BlynkEdgent.begin();

}

BLYNK_WRITE(V0) {
pos = param.asInt();
myservo.write(pos);
}


BLYNK_WRITE(V2) {
  forward = param.asInt();
}

BLYNK_WRITE(V3) {
  backward = param.asInt();
}

BLYNK_WRITE(V5) {
  left = param.asInt();
}

BLYNK_WRITE(V4) {
  right = param.asInt();
}

BLYNK_WRITE(V1) {
  Speed = param.asInt();
}
BLYNK_WRITE(V10) {
  data = param.asInt();
  if (data==1){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  sensorValue = analogRead(A0);
  pressure = bmp.readPressure() / 100.0F;
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  
  Blynk.virtualWrite(V7 , h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V8, sensorValue);
  Blynk.virtualWrite(V9, pressure);
  Blynk.virtualWrite(V11, altitude);
    }
}

void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  BlynkEdgent.run();
  smartcar();

}
void carforward() {
  analogWrite(ENA, Speed);
//  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}
void carbackward() {
  analogWrite(ENA, Speed);
//  analogWrite(ENB, Speed);
    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 

}
void carturnleft() {
  analogWrite(ENA, Speed);
//  analogWrite(ENB, Speed);

    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnright() {
  analogWrite(ENA, Speed);
//  analogWrite(ENB, Speed);
    digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
