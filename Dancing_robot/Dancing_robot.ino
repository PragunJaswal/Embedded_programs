#include <Servo.h> 
int servoPin1 = 4; 
int servoPin2 = 7; 
int servoPin3 = 9; 
int servoPin4 = 11; 

Servo Servo1; 
Servo Servo2; 
Servo Servo3; 
Servo Servo4; 

void setup() 
{ 
   Servo1.attach(servoPin1); 
   Servo2.attach(servoPin2); 
   Servo3.attach(servoPin3); 
   Servo4.attach(servoPin4); 
   
}
void loop()
{ 
   Servo1.write(0); 
   Servo2.write(0);
   Servo3.write(0);
   Servo4.write(0);
   delay(2000);
   Servo1.write(90); 
   Servo2.write(90);
   Servo3.write(90);
   Servo4.write(90);
   delay(2000);
}
