#define x A0
#define y A1

void setup() {
  // put your setup code here, to run once:
pinMode(x,INPUT);
pinMode(y,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int valx = analogRead(x);
int valy = analogRead(y);

Serial.println("started");
Serial.println(valx);
Serial.println(valy);

if (valx == 1023 and valy == 500){
  digital
  
  }


}
