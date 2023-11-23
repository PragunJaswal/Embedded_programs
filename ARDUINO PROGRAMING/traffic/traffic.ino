int r1 = 13;
int y1 = 12;
int g1 = 11;
int r2 = 10;
int y2 = 9;
int g2 = 8;

void setup() {
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
pinMode(8, OUTPUT);
}

void loop() {

digitalWrite(r1,HIGH);
digitalWrite(y2,HIGH);
delay(3000);

digitalWrite(y2,LOW);
digitalWrite(g2,HIGH);
delay(7000);

digitalWrite(r1,LOW);
digitalWrite(g2,LOW);
digitalWrite(y1,HIGH);

digitalWrite(y2,HIGH);
delay(3000);

digitalWrite(y2,LOW);
digitalWrite(r2,HIGH);
delay(3000);

digitalWrite(y1,LOW);
digitalWrite(g1,HIGH);
delay(7000);

digitalWrite(g1,LOW);
digitalWrite(r2,LOW);
digitalWrite(y1,HIGH);
digitalWrite(y2,HIGH);
delay(3000);

digitalWrite(y1,LOW);
digitalWrite(y2,LOW);
}
