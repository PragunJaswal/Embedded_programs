
#define in1 13 //Motor1  L298 Pin in1 
#define in2 12//Motor1  L298 Pin in2 
#define in3 11 //Motor2  L298 Pin in3 
#define in4 10 //Motor2  L298 Pin in4 

void setup(){ 
Serial.begin(9600);
delay(100);


pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 

delay(1000);
}


void loop(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH);  //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin
delay(3000);
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin
delay(3000);
}
