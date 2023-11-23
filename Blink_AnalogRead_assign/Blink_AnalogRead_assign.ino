#include <Arduino_FreeRTOS.h>

// define two tasks for Blink lED &  Read LM35 values Analog Values
void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);
int state = true;  //flag to monitor the state of temperature

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, INPUT);

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink, "Blink"  // A name of task
    ,
    128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL);

  xTaskCreate(
    TaskAnalogRead, "AnalogRead", 128  // Stack size
    ,
    NULL, 1  // Priority
    ,
    NULL);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void)pvParameters;

  /*
  Blink
  Turns on and off an BUILTIN_LED repeatedly.
  Based on the state variable data the led on and off time is to be decised.


  when temperature is below 30 deg Celsius state variable is true, hence we to
   blink the led every 250ms for that in first 125ms we have to turn on the led and for next 125ms we have to turn it off.
  when temperature is above 30 deg Celsius state variable is false, hence we to
   blink the led every 500ms for that in first 250ms we have to turn on the led and for next 250ms we have to turn it off.  

*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)  // A Task shall never return or exit.
  {
    // make decision basd on state variable either to blink led fast or slow
    if (state == true) {                     //to blink led fast
      digitalWrite(LED_BUILTIN, HIGH);       // turn the LED on (HIGH is the voltage level)
      vTaskDelay(250 / portTICK_PERIOD_MS);  // wait for 250ms
      digitalWrite(LED_BUILTIN, LOW);        // turn the LED off by making the voltage LOW
      vTaskDelay(250 / portTICK_PERIOD_MS);  // wait for 250ms
    } else {                                 //to blink led fast
      digitalWrite(LED_BUILTIN, HIGH);       // turn the LED on (HIGH is the voltage level)
      vTaskDelay(125 / portTICK_PERIOD_MS);  // wait for 500ms
      digitalWrite(LED_BUILTIN, LOW);        // turn the LED off by making the voltage LOW
      vTaskDelay(125 / portTICK_PERIOD_MS);  // wait for 500ms
    }
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void)pvParameters;

  /*
  AnalogReadSerial
  Reads an analog input on pin A0, convert the following adc reading to temperature, 
  prints the result to the serial monitor and change the state of the state variable.

*/

  for (;;) {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    float voltage = sensorValue * (5.0 / 1024.0);
    float temperatureC = voltage * 100;
    Serial.print(temperatureC);
    Serial.print(" C || ");
    state = (temperatureC > 30) ? true : false;  //ternary operator to change the state
    Serial.println(state);
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}
