void setup() {
  // put your setup code here, to run once:
pinMode(11, OUTPUT);
pinMode(3, INPUT);

}

void loop() {
if (digitalRead(3) == HIGH)

{digitalWrite(11,HIGH);
delay(5);
  }
else
{digitalWrite(11,LOW);
delay(5);
  }

}
