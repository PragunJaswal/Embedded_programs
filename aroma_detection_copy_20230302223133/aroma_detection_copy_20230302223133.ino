#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the pins for the e-nose sensors
const int sensorPin1 = A0;
// const int sensorPin2 = A1;
const int sensorPin3 = A3;
const int sensorPin4 = A2;
// const int sensorPin5 = A4;

// Define the threshold values for each sensor
const int threshold1 = 500;
const int threshold2 = 600;
const int threshold3 = 700;
const int threshold4 = 800;

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  // Read the values from each sensor
  int sensor_mq135 = analogRead(sensorPin3);
  // int sensor_mq9 = analogRead(sensorPin2);
  // int sensor_mq2 = analogRead(sensorPin5);
  int sensor_mq3 = analogRead(sensorPin4);
  int sensor_mq6 = analogRead(sensorPin1);



  Serial.println("VALUES :: ");
  Serial.print("MQ135 = ");
  Serial.println(sensor_mq135);
  // Serial.print("MQ9 = ");
  // Serial.println(sensor_mq9);
  // Serial.print("MQ2 = ");
  // Serial.println(sensor_mq2);
  Serial.print("MQ3 = ");
  Serial.println(sensor_mq3);
  Serial.print("MQ6 = ");
  Serial.println(sensor_mq6);
  Serial.println("");
  delay(100);


  // for ms excel data

  // Serial.print(sensor_mq135);
  // Serial.print(",");
  // // Serial.print(sensor_mq9);
  // // Serial.print(",");
  // // Serial.print(sensor_mq2);
  // // Serial.print(",");
  // Serial.print(sensor_mq3);
  // Serial.print(",");
  // Serial.print(sensor_mq6);
  // Serial.println(",");
  // delay(500);




  // Check if the sensor values are above the threshold values

  if (sensor_mq135 < 10 ) {
    Serial.println(" pure Air");
    display.setTextSize(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Pure       Air");
    display.display();
  }

  else if (sensor_mq135 >= 25 and sensor_mq135 < 150 and sensor_mq6 > 100 and sensor_mq6 < 150 and sensor_mq3 > 300 and sensor_mq3 < 600 ) {

    Serial.println("Matchstick detected");
    display.setTextSize(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Matchstick detected");
    display.display();

  }


  else  if (sensor_mq135 > 30 and sensor_mq3 > 500 and sensor_mq3 < 750 and sensor_mq6 > 100  ) {
      Serial.println("Agarbatti detected");
      display.setTextSize(2);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Agarbatti detected");
      display.display();
    }

  else if (sensor_mq3 > 800 and sensor_mq3 < 1000 and sensor_mq6 > 80) {

    if (sensor_mq135 < 100) {
      Serial.println("perfume    detected");
      display.setTextSize(2);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("perfume    detected");
      display.display();
    }
  }


  else if ( sensor_mq135 < 80 and sensor_mq3 > 500 and sensor_mq3 < 800 and sensor_mq6 < 70) {
 
    Serial.println("Camphor detected");
    display.setTextSize(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Camphor   detected");
    display.display();
  }


  else if (sensor_mq3 > 170 and sensor_mq135 > 20 and sensor_mq6 > 95) {

      Serial.println("Liquid Tea detected");
      display.setTextSize(2);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Tea         detected");
      display.display();
  }


  else if (sensor_mq3 > 150 and sensor_mq3 < 600 and sensor_mq6 > 90 and sensor_mq135 > 20) {
    Serial.println("Liquid Coffee detected");
    display.setTextSize(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Coffee        detected");
    display.display(); 
  }


else {
    Serial.println("Normal Air");
    display.setTextSize(2);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Normal Air");
    display.display();

}
  // Delay for a short period to avoid sending too many messages
  delay(500);
}
