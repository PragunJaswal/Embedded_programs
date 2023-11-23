
#include <SoftwareSerial.h>  //including library for Software Serial communication
#include <Servo.h>

SoftwareSerial mySerial(3, 2);  //(RX, TX)


Servo myservo;
//defining all the pins of Arduino
#define m1 8
#define m2 9
#define m3 10
#define m4 11
#define ENA 12
#define light1 4
#define light2 5
#define sound A1
int po = 80;
int speed = 255;
bool flag = false;
bool flag1 = false;
bool forward =false;

int trigPin = 6;  // Trigger
int echoPin = 4;  // Echo
long duration, cm, inches;

void setup() {
  //setting all the pins
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(sound, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  myservo.attach(5);
  //defining baudrate
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(50);

  // Serial.println(analogRead(A0));
  if (mySerial.available())  //if communication is going on
  {
    char val = mySerial.read();  //Read the data recieved
    Serial.println("Recieved data is " + (String)val);
    if (val == 'F' ) {
      //forward

      if (analogRead(A0) >= 300) {
        //all off
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        digitalWrite(sound, LOW);
        delay(1000);

      } else {
        analogWrite(ENA, speed);
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
        Serial.println("Going forward!");

      }
    }
    if (val == 'B') {
      //backward
      analogWrite(ENA, speed);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
      Serial.println("Going backward!");
    }
    if (val == 'L') {
      //left
      analogWrite(ENA, speed);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      Serial.println("Going left!");
    }
    if (val == 'R') {
      //right
      analogWrite(ENA, speed);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
      Serial.println("Going right!");
    }
    if (val == 'l') {
      //forward left
      analogWrite(ENA, speed);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      Serial.println("Going forward left!");
    }
    if (val == 'r') {
      //forward right
      analogWrite(ENA, speed);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      Serial.println("Going forward right!");
    }
    if (val == 'm') {
      //backward left
      analogWrite(ENA, speed);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    if (val == 'n') {
      //backward right
      analogWrite(ENA, speed);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
    if (val == 'S') {
      //all off
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      digitalWrite(sound, LOW);
    }
    if (val == 'M') {
      flag = !flag;
      digitalWrite(7, flag);
    }
    if (val == 'X') {
      digitalWrite(sound, HIGH);
    }
    else{
      digitalWrite(sound, LOW);

    }
    if (val == 'N') {
      flag1 = !flag1;
      digitalWrite(13, flag1);
    }

     else if (val == 'J') {
      char val = mySerial.read();  //Read the data recieved
      if (val == '1') {
        myservo.write(40);
      }
      if (val == '1') {
        myservo.write(50);
      }
      if (val == '2') {
        myservo.write(60);
      }
      if (val == '3') {
        myservo.write(70);
      }
      if (val == '4') {
        myservo.write(80);
      }
      if (val == '5') {
        myservo.write(90);
      }
      if (val == '6') {
        myservo.write(100);
      }
      if (val == '7') {
        myservo.write(110);
      }
      if (val == '8') {
        myservo.write(120);
      }
      if (val == '9') {
        myservo.write(130);
      }
    }
  }
      if (cm <= 8) {

    //all off

    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(sound, LOW);

    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);

    delay(1000);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    Serial.println("Going backward!");
    delay(1000);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(13, LOW);
    }
  if (analogRead(A0) >= 300) {

    //all off

    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(sound, LOW);

    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);

    delay(1000);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    Serial.println("Going backward!");
    delay(1000);
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(13, LOW);
  }
}
