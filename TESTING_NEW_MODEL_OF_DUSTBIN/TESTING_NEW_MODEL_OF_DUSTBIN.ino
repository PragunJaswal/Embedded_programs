#include <Servo.h>

Servo myservo; 


const int trig = 9;
const int echo = 10;
const int trig1 = D7;
const int echo1 = D8;
const int trig2 = D5;
const int echo2 = D6;
long durat;
int distance;
int bin = 0;
long durat1;
int distance1;
int bin1 = 0;
long durat2;
int distance2;
int bin2 = 0;

void setup(){
    Serial.begin(9600);
    myservo.attach(D3);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT_PULLUP);
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT_PULLUP);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT_PULLUP);
    myservo.write(30);
}

void loop() {

    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    durat2 = pulseIn(echo2, HIGH);
    distance2 = durat2 * 0.034 / 2;
    Serial.println(distance2);
    delay(200);

    if (distance2<15){
      myservo.write(30);
      delay(2000);
      
      }
      else{
        myservo.write(6 0);
        }
 
}

void binlevel(){
      digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2;
    Serial.println(distance);        //Uncomment to measure distance of bin
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
    Serial.println(distance1);        //Uncomment to measure distance of bin
    bin1=map(distance1, 26, 0, 0,100);
//    Serial.println(bin1);
    delay(200);

  
  
  
  
  }
