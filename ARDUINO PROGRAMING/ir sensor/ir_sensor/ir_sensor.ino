void setup() {
  // put your setup code here, to run once:
pinMode(12, OUTPUT);
pinMode(3, INPUT);

}

void loop() {
if (digitalRead(3) == HIGH)

{digitalWrite(12,HIGH);
delay(10);

  }
else
{digitalWrite(12,LOW);
delay(10);
  }

}
