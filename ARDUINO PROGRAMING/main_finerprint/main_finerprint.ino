#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial mySerial(2, 3);

const int rxPin = 0;
const int txPin = 1; 
SoftwareSerial bt(rxPin, txPin);
const int Loads[] = {6};
int state = 0;
int flag = 0;


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  {
for (int i=0;i<1;i++)
{
pinMode(Loads[i], OUTPUT);
}
bt.begin(9600);
for (int i=0;i<1;i++)
{digitalWrite(Loads[i], LOW);
}}
       
  
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("fingertest");
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  lcd.begin(16, 2);




  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
      
  } else {
    Serial.println("Did not find fingerprint sensor :(");
   
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
   delay(10);
    lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("FINGERPRINT ");
      lcd.setCursor(0, 1);
      lcd.print("         LOCKER ");
}

void loop()   

{

   lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("FINGERPRINT ");
      lcd.setCursor(0, 1);
      lcd.print("         LOCKER ");
      
if(bt.available() > 0)


{
state = bt.read();
flag=0;
}
switch(state)
{
case '0':digitalWrite(Loads[0], HIGH);
flag=1;
break;
case '1':digitalWrite(Loads[0], LOW);
flag=1;
break;
case '2':digitalWrite(Loads[0], LOW);
digitalWrite(Loads[1], LOW);
digitalWrite(Loads[2], LOW);
digitalWrite(Loads[3], LOW);
flag=1;
break;}

  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
       delay(1);
       lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("sensor connected");
      lcd.setCursor(0, 1);
     
      lcd.print("No finger detected");
       delay(1);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
     lcd.clear();
       lcd.setCursor(0, 0);
      lcd.print("sensor connected");
      lcd.setCursor(0, 1);
     
      lcd.print("finger detected");
      
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  {digitalWrite(7, HIGH);
  delay(3000);
  digitalWrite(7, LOW);
  Serial.print("Not Found"); 
  lcd.print("Not Found");
  Serial.print("Error"); 
  return finger.fingerID;
 }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
lcd.print("Found ID #"); lcd.print(finger.fingerID);
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.fingerFastSearch();

  
    if (p == FINGERPRINT_OK) ;
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FINGERPRINT ");
    lcd.setCursor(0, 1);
    lcd.print("Not Found");
    
    
    }
    
  if (p != FINGERPRINT_OK)  return -1;    // found a match!

  {
   
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);
     delay(1);
       lcd.clear();
        lcd.setCursor(0,0);
       lcd.print("Finger Print #"); lcd.print(finger.fingerID);
       lcd.setCursor(0, 1);
      lcd.print("    Matched");
      
    delay(800);
     digitalWrite(6, HIGH);
    delay(3000);
    digitalWrite(6, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FINGERPRINT ");
    lcd.setCursor(0, 1);
    lcd.print("         LOCKER ");
  
  }

}
