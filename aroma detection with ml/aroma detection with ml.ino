#include <TensorFlowLite_ESP32.h>
#include <TensorFlowLite_ESP32.h>
#include <Arduino.h>

// Define the number of input and output neurons for the neural network
const int inputNeurons = 4;
const int outputNeurons = 3;

// Define the pin numbers for the e-nose sensors
const int sensorPin1 = 32;
const int sensorPin2 = 33;
const int sensorPin3 = 34;
const int sensorPin4 = 35;

// Define the threshold values for each sensor
const int threshold1 = 500;
const int threshold2 = 600;
const int threshold3 = 700;
const int threshold4 = 800;

// Create a TensorFlowLite object for the neural network
TensorFlowLite_ESP32 tflite;

// Define the neural network model file
const char* modelFileName = "/model.tflite";

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Initialize the e-nose sensors as inputs
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);

  // Initialize the TensorFlowLite object with the model file
  tflite.begin(modelFileName);
}

void loop() {
  // Read the values from each sensor
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);

  // Create an input array for the neural network
  float inputArray[inputNeurons] = {
    (float)sensorValue1,
    (float)sensorValue2,
    (float)sensorValue3,
    (float)sensorValue4
  };

  // Normalize the input values to a range of 0 to 1
  for (int i = 0; i < inputNeurons; i++) {
    inputArray[i] = inputArray[i] / 1023.0;
  }

  // Make a prediction with the neural network
  float outputArray[outputNeurons];
  tflite.predict(inputArray, outputArray);

  // Find the index of the highest output value
  int maxIndex = 0;
  float maxValue = outputArray[0];
  for (int i = 1; i < outputNeurons; i++) {
    if (outputArray[i] > maxValue) {
      maxIndex = i;
      maxValue = outputArray[i];
    }
  }

  // Print the predicted aroma
  switch (maxIndex) {
    case 0:
      Serial.println("Aroma 1 detected");
      break;
    case 1:
      Serial.println("Aroma 2 detected");
      break;
    case 2:
      Serial.println("Aroma 3 detected");
      break;
  }

  // Delay for a short period to avoid sending too many messages
  delay(1000);
}
