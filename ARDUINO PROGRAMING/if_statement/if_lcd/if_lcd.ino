#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int button(1);
const int led(13);
int buttonstate = 0;
void setup() {
pinMode(13, OUTPUT);
pinMode(1,INPUT);

}

void loop() {
 buttonstate = digitalRead (1);
  lcd.clear();
  if
  (buttonstate == LOW)
    //digitalWrite (buttonstate == HIGH)
   {
    digitalWrite(led, HIGH);
    lcd.print("started");
    }
   
else 
{
  digitalWrite(led, LOW);
  lcd.print("stopped");
}
 
}
