int frequency = 70000; //Set frequency in Hertz

double delayTime = 100 / (frequency * 2);

void setup() 
{
pinMode(13, OUTPUT);  
pinMode(11, OUTPUT);
}

void loop() 
{
 digitalWrite(11, LOW);
 digitalWrite(13, HIGH);
 delay(delayTime);

 digitalWrite(13, LOW);
 digitalWrite(11, HIGH);
 delay(delayTime);
}