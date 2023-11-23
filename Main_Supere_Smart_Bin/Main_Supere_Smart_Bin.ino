
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLGb6RAVvC"
#define BLYNK_DEVICE_NAME "Super Smart Dustbin"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <LiquidCrystal_I2C.h>
#include "BlynkEdgent.h"
#include <Servo.h>

Servo myservo; 


const int trig = 9;
const int echo = 10;
const int trig1 = D7;
const int echo1 = D8;
const int trig2 = D5;
const int echo2 = D6;
const int input = A0;
long durat;
int distance;
int bin = 0;
long durat1;
int distance1;
int bin1 = 0;
long durat2;
int distance2;
int bin2 = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);   //if lcd not work then change the address to 0x3F

void setup()
{
    Serial.begin(9600);
    myservo.attach(D3);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT_PULLUP);
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT_PULLUP);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT_PULLUP);
    pinMode(input,INPUT_PULLUP);
    
    myservo.write(30);
    delay(100);
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("HELLo");
    lcd.setCursor(0, 1);
    lcd.print("CoNNeCTiNg WITH WiFi");

  BlynkEdgent.begin();
}

void loop() {

  
    BlynkEdgent.run();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No Object");
        
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    durat2 = pulseIn(echo2, HIGH);
    distance2 = durat2 * 0.034 / 2;
    Serial.print("distance= ");
    Serial.println(distance2);
    delay(200);
    Serial.println(analogRead(input));

while (distance2<20){

   if(analogRead(input)<1010){
    Serial.print("Analog input= ");
    Serial.println(analogRead(input));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wet Garabage");
    myservo.write(0);
    delay(2000);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2;
//    Serial.println(distance);        //Uncomment to measure distance of bin
    bin=map(distance, 25, 0, 0,100);
//    Serial.println(bin);
    delay(200);
    digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    durat1 = pulseIn(echo1, HIGH);
    distance1 = durat1 * 0.034 / 2;
//    Serial.println(distance1);        //Uncomment to measure distance of bin
    bin1=map(distance1, 26, 0, 0,100);
//  Serial.println(bin1);
Blynk.virtualWrite(V0, bin);
Blynk.virtualWrite(V1, bin1);
    break;
    delay(2000);
    
    }
    else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dry Garabage");
    myservo.write(60);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2;
//    Serial.println(distance);        //Uncomment to measure distance of bin
    bin=map(distance, 25, 0, 0,100);
//    Serial.println(bin);
    delay(200);
      digitalWrite(trig1, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    durat1 = pulseIn(echo1, HIGH);
    distance1 = durat1 * 0.034 / 2;
//    Serial.println(distance1);        //Uncomment to measure distance of bin
    bin1=map(distance1, 26, 0, 0,100);
//    Serial.println(bin1);
Blynk.virtualWrite(V0, bin);
Blynk.virtualWrite(V1, bin1);
    break;
    delay(2000);
      }
       }
 delay(200);
  }
