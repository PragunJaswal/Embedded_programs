const int button(1);
const int led(13);
int buttonstate = 0;
void setup() {
pinMode(13, OUTPUT);
pinMode(1,INPUT);
}

void loop() {
 buttonstate = digitalRead (1);
 
  if
  (buttonstate == LOW)
    //digitalWrite (buttonstate == HIGH)
   {
    digitalWrite(led, HIGH);
    }
   
else 
{
  digitalWrite(led, LOW);
}
 
}
