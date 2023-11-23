#define SENSE A0 

void setup()
{
pinMode(SENSE, INPUT);
pinMode(13, OUTPUT);

}
void loop()
{
if(digitalRead(SENSE))
{
 digitalWrite(LED_BUILTIN, LOW);
 pinMode(13, LOW);
}
else
{
  delay (2000);
  if(digitalRead(SENSE))
  {
 digitalWrite(LED_BUILTIN, LOW);
 pinMode(13, LOW);
}
  else
  digitalWrite(LED_BUILTIN, HIGH);  
   pinMode(13, HIGH);
  }
}
