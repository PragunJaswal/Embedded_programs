/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
myservo.attach(2);  // attaches the servo on pin 9 to the servo object
myservo.attach(4);
myservo.attach(3);
myservo.attach(5);

}

void loop() {
    myservo.write(90);        
    delay(15);                      
    myservo2.write(90);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
   myservo3.write(90);        
    delay(15);                      
    myservo4.write(90);              // tell servo to go to position in variable 'pos'
    delay(15); 

delay(1000);
    myservo.write(0);        
    delay(15);                      
    myservo2.write(0);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
   myservo3.write(0);        
    delay(15);                      
    myservo4.write(0);              // tell servo to go to position in variable 'pos'
    delay(15); 
  delay(1000);
}
