#include <Servo.h>

Servo myservo; 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);   //if lcd not work then change the address to 0x3F
const int trig2 = 10;
const int echo2 = 9;
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


void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(5, 0);
    lcd.print("HELLo");
    lcd.setCursor(0, 1);
    lcd.print("CoNNeCTiNg WiFi");
    myservo.attach(6);
    pinMode(trig2, OUTPUT);
    pinMode(echo2,INPUT);
    pinMode(input,INPUT);   
    myservo.write(40);
    delay(1000);
}

void loop() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Object");
    delay(1000);
    myservo.write(40);
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    durat2 = pulseIn(echo2, HIGH);
    distance2 = durat2 * 0.034 / 2;
    Serial.print("distance= ");
    Serial.println(distance2);
    Serial.print("Analog input= ");
    Serial.println(analogRead(input));
    delay(100);
while (distance2<21 ){
  delay(30);
  if (analogRead(input)>1020){
    myservo.write(0);
    Serial.print("dry waste ");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("dry Garabage");
   
    delay(2000);
    break;
    }
  else{
    
    Serial.print("wet waste ");
    myservo.write(120);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("wet Garabage");
    delay(2000);
    break;
    }

}
myservo.write(40);
delay(500);
}
