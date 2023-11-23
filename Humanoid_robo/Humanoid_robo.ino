#include <Servo.h>  
 
Servo servo1; 
Servo servo2; 
Servo servo3; 
Servo servo4; 
 
int pos1 = 0; 
int pos2 = 0; 
int pos3 = 0; 
 
void setup()  
{  
  servo1.attach(4);        //left foot
  servo2.attach(7);        //right foot
  servo3.attach(9);        //right leg
  servo4.attach(11);       //left leg
   
 
  servo1.write(90);               
  servo2.write(90);               
  servo3.write(90);               
  servo4.write(90); 
   
  delay(2000);  //Stay in Lock Position for 2 Sec 
}  
 
void loop()  
{  
  for(pos1 = 90, pos2 = 90; pos1 > 70, pos2 > 70; pos1--, pos2--)  //left leg up 
  {                                   
    servo1.write(pos1);               
    servo2.write(pos2);               
    servo3.write(90);               
    servo4.write(90);               
    delay(20);                        
  } 
 
  for(pos1 = 90, pos2 = 90; pos1 < 100, pos2 < 100; pos1++, pos2++)     //move forward 
  {                                 
    servo1.write(70);               
    servo2.write(70);               
    servo3.write(pos1);               
    servo4.write(pos2);               
    delay(20);                        
  }  
   
  for(pos1 = 70, pos2 = 70; pos1 < 90, pos2 < 90; pos1++, pos2++)     //left leg down 
  {                                 
    servo1.write(pos1);               
    servo2.write(pos2);               
    servo3.write(100);               
    servo4.write(100);               
    delay(20);                        
  }  
   
  for(pos1 = 90, pos2 = 90; pos1 < 110, pos2 < 110; pos1++, pos2++)     //right leg up 
  {                                 
    servo1.write(pos1);               
    servo2.write(pos2);               
    servo3.write(100);               
    servo4.write(100);               
    delay(20);                        
  }  
   
  for(pos1 = 100, pos2 = 100; pos1 > 90, pos2 > 90; pos1--, pos2--)     //move forward 
  {                                 
    servo1.write(110);               
    servo2.write(110);               
    servo3.write(pos1);               
    servo4.write(pos2);               
    delay(20);                        
  }  
   
  for(pos1 = 110, pos2 = 110; pos1 > 90, pos2 > 90; pos1--, pos2--)     //right leg down 
  {                                 
    servo1.write(pos1);               
    servo2.write(pos2);               
    servo3.write(90);               
    servo4.write(90);               
    delay(20);                        
  }  
   
  delay(100); 
}
