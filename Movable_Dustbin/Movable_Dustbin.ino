#define BLYNK_TEMPLATE_ID "TMPLMql9O2A1"
#define BLYNK_DEVICE_NAME "robo 2"

#define enA D4//Enable1 L298 Pin enA 
#define in1 D5 //Motor1  L298 Pin in1 
#define in2 D6 //Motor1  L298 Pin in1 
#define in3 D7 //Motor2  L298 Pin in1 
#define in4 D8 //Motor2  L298 Pin in1 
//#define enB D10 //Enable2 L298 Pin enB

#define R_S D1 //ir sensor Right
#define L_S D2 //ir sensor Left
#define R_S1 D0 //ir sensor Right
#define L_S1 D10 //ir sensor Left
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#include "BlynkEdgent.h"
int pos = 0;
int pos2 = 0;
void setup() { // put your setup code here, to run once
  Serial.begin(9600);
  delay(100);

  BlynkEdgent.begin();
  pinMode(R_S, INPUT); // declare if sensor as input
  pinMode(L_S, INPUT); // declare ir sensor as input
  pinMode(R_S1, INPUT); // declare if sensor as input
  pinMode(L_S1, INPUT); // declare ir sensor as input

  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
  //pinMode(enB, OUTPUT); // declare as output for L298 Pin enB

  analogWrite(enA, 255); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed
  //analogWrite(enB, 150); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed
  delay(500);
}

BLYNK_WRITE(V0) {
  pos = param.asInt();
}

BLYNK_WRITE(V1) {
  pos2 = param.asInt();
}


void loop() {
  BlynkEdgent.run();

  if (pos == 1) {
    if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 1)) {
      digitalWrite(in1, HIGH); //Right Motor forword Pin
      digitalWrite(in2, LOW);  //Right Motor backword Pin
      digitalWrite(in3, LOW);  //Left Motor backword Pin
      digitalWrite(in4, HIGH); //Left Motor forword Pin
    }   //if Right Sensor and Left Sensor are at White color then it will call forword function


    if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) {
      digitalWrite(in1, LOW);  //Right Motor forword Pin
      digitalWrite(in2, HIGH); //Right Motor backword Pin
      digitalWrite(in3, LOW);  //Left Motor backword Pin
      digitalWrite(in4, HIGH); //Left Motor forword Pin } //if Right Sensor is Black and Left Sensor is White then it will call turn Right function
    }
    if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
      digitalWrite(in1, HIGH); //Right Motor forword Pin
      digitalWrite(in2, LOW);  //Right Motor backword Pin
      digitalWrite(in3, HIGH); //Left Motor backword Pin
      digitalWrite(in4, LOW);  //Left Motor forword Pin }  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
    }

    if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
      digitalWrite(in1, LOW); //Right Motor forword Pin
      digitalWrite(in2, LOW); //Right Motor backword Pin
      digitalWrite(in3, LOW); //Left Motor backword Pin
      digitalWrite(in4, LOW); //Left Motor forword Pin
    } //if Right Sensor and Left Sensor are at Black color then it will call Stop function
  }

  if (pos2  == 2) {
    if ((digitalRead(R_S1) == 1) && (digitalRead(L_S1) == 1)) {
      digitalWrite(in1, LOW); //Right Motor forword Pin
      digitalWrite(in2, HIGH);  //Right Motor backword Pin
      digitalWrite(in3, HIGH);  //Left Motor backword Pin
      digitalWrite(in4, LOW); //Left Motor forword Pin
    }   //if Right Sensor and Left Sensor are at White color then it will call forword function


    if ((digitalRead(R_S1) == 1) && (digitalRead(L_S1) == 0)) {
      digitalWrite(in1, LOW);  //Right Motor forword Pin
      digitalWrite(in2, HIGH); //Right Motor backword Pin
      digitalWrite(in3, LOW);  //Left Motor backword Pin
      digitalWrite(in4, HIGH); //Left Motor forword Pin } //if Right Sensor is Black and Left Sensor is White then it will call turn Right function
    }
    if ((digitalRead(R_S1) == 0) && (digitalRead(L_S1) == 1)) {
      digitalWrite(in1, HIGH); //Right Motor forword Pin
      digitalWrite(in2, LOW);  //Right Motor backword Pin
      digitalWrite(in3, HIGH); //Left Motor backword Pin
      digitalWrite(in4, LOW);  //Left Motor forword Pin }  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
    }

    if ((digitalRead(R_S1) == 0) && (digitalRead(L_S1) == 0)) {
      digitalWrite(in1, LOW); //Right Motor forword Pin
      digitalWrite(in2, LOW); //Right Motor backword Pin
      digitalWrite(in3, LOW); //Left Motor backword Pin
      digitalWrite(in4, LOW); //Left Motor forword Pin } //if Right Sensor and Left Sensor are at Black color then it will call Stop function
    }
  }
}
