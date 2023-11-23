#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Servo.h>
Servo servo;
SimpleTimer timer;

const int trig = D0;
const int echo = D1;
const int trigPin1 = D7;
const int echoPin1 = D6;
long duration;
int distance; 
long durat;
long duration1;
int distance1;
int distance2;
int bin = 0;
int diff = 0;
char auth[] = "yc_Ce1J5JcPkQ8-zOHuO5yx0yt1ejy49";
char ssid[] = "Realme";
char password[] =  "987654321";
int temp = 0;
int temp1 = 0;
int current;
BLYNK_WRITE(V3) {
servo.write(param.asInt());
      }
void sendSensor()
{    
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2; 
    ultrasonic(); 
     Serial.println(distance);
  if(distance<35)
  {
    servo.write(180);
    for(int i=0; i<45; i++)
    {
    ultrasonic(); 
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2; 
    
      delay(90);
      }
  if (distance>13 && distance<50)    
      
   {
    servo.write(0);
    delay(500);
  }
 }
}
void ultrasonic()
{   
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseInLong(echoPin1, HIGH);
     if (duration1>215 && duration1<2515) 
    {
    distance1 = duration1 * 0.034 / 2;   
    }
    current = distance1;
    diff = current-temp;

    if (distance1<45 && distance1>2)
    {
      
    distance2=distance1;
    delay(5);
    }
  
    if (diff < 10 && temp1 < 45) 
    {
      bin=map(temp, 42, 0, 0,100);
      Blynk.virtualWrite(V6, bin);

      temp = current;
    }
    else{
      
    Serial.println("error");
    Serial.println(distance1);
      temp = current;
      delay(100);
    }
   if (bin>=80)
   Blynk.email("pragunjaswal2@gmail.com","Dustbin 1 in filled","Dustbin near stairs is filled more than 80%, please recycle it !!");
     
}
void setup()
{
  
  Serial.begin(9600);
  servo.attach(D5);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT_PULLUP);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT_PULLUP);
  Serial.begin(9600);


  WiFi.mode(WIFI_STA);
  Blynk.begin(auth,ssid,password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED)
  { Serial.print("not connected\n" );
    Serial.print(WiFi.status());
    delay(200);
     }
 Serial.println();
 Serial.println("connected");
 Serial.print(WiFi.localIP() );
  
  delay(100); 
  servo.write(0);
}

void loop() 
{
 
  timer.setInterval(10L, sendSensor); 
  Blynk.run();
  timer.run();
}
