#define relay1 2
#define relay2 3
#define relay3 4
#define relay4 5

#define hbas 6

#define led1 7
#define led2 8
#define led3 9
#define led4 10


#define bat1 A0
#define bat2 A1
#define bat3 A2
#define bat4 A3

int theshold = 355;  //you have to calibrate these values  according to your volatge divider ckt
int theshold2 = 824;
int r1, r2, r3, r4 = 0;
int p1, p2, p3, p4 = 0;
int discharge = 0;
int delaytime = 1000;
int asd = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(bat1, INPUT);
  pinMode(bat2, INPUT);
  pinMode(bat3, INPUT);
  pinMode(bat4, INPUT);
  pinMode(hbas, INPUT);
  Serial.begin(9600);

}

void loop() {

  p1, p2, p3, p4 = 0;
  r1, r2, r3, r4 = 0;
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.println("Mode0");

  while (digitalRead(hbas) == 1) { //hbas is on
    Serial.println("Values");
    float a = analogRead(bat1);
    float b = analogRead(bat2);
    float c = analogRead(bat3);
    float d = analogRead(bat4);
    Serial.print("battery 1 =");
    Serial.println(a / 60);
    Serial.print("battery 2 =");
    Serial.println(b / 60);
    Serial.print("battery 3 =");
    Serial.println(c / 60);
    Serial.print("battery 4 =");
    Serial.println(d / 60);



    //
    //Serial.print ("charge is ");
    //Serial.println(discharge);


    while (discharge) {
      float a = analogRead(bat1);
      float b = analogRead(bat2);
      float c = analogRead(bat3);
      float d = analogRead(bat4);
      Serial.print("battery 1 =");
      Serial.println(a / 60);
      Serial.print("battery 2 =");
      Serial.println(b / 60);
      Serial.print("battery 3 =");
      Serial.println(c / 60);
      Serial.print("battery 4 =");
      Serial.println(d / 60);
      if (analogRead(bat1) >= theshold and analogRead(bat2) >= theshold and analogRead(bat3) >= theshold and analogRead(bat4) >= theshold and asd) {
        r1, r2, r3, r4 = 1;


        digitalWrite(relay1, LOW);
        digitalWrite(relay2, HIGH);
        digitalWrite(relay3, HIGH);
        digitalWrite(relay4, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        Serial.println("First if");
        asd = 0;
      }
      if (analogRead(bat1) < theshold and analogRead(bat2) >= theshold and analogRead(bat3) >= theshold and analogRead(bat4) >= theshold) {
        r2, r3, r4 = 1;
        r1 = 0;
        Serial.println("2 if");
        digitalWrite(relay2, LOW);
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        delay(delaytime);
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, LOW);
        digitalWrite(relay3, HIGH);
        digitalWrite(relay4, HIGH);
      }

      if (analogRead(bat1) < theshold and analogRead(bat2) < theshold and analogRead(bat3) >= theshold and analogRead(bat4) >= theshold) {
        r3, r4 = 1;
        r1, r2 = 0;
        Serial.println("3 if");

        digitalWrite(relay3,LOW);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        delay(delaytime);
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, HIGH);
        digitalWrite(relay3, LOW);
        digitalWrite(relay4, HIGH);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
      }
      if (analogRead(bat1) < theshold and analogRead(bat2) < theshold and analogRead(bat3) < theshold and analogRead(bat4) >= theshold ) {
        r4 = 1;
        r1, r2, r3 = 0;
        Serial.println("4 if");
        digitalWrite(relay4,LOW);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, HIGH);
        delay(delaytime);
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, HIGH);
        digitalWrite(relay3, HIGH);
        digitalWrite(relay4, LOW);

      }
      if (analogRead(bat1) < theshold and analogRead(bat2) < theshold and analogRead(bat3) < theshold and analogRead(bat4) < theshold)  {
        r1, r2, r3, r4 = 0;
        Serial.println("5 if");
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, HIGH);
        digitalWrite(relay3, HIGH);
        digitalWrite(relay4, HIGH);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
      }
      if (analogRead(bat1) < theshold and analogRead(bat2) < theshold and analogRead(bat3) < theshold and analogRead(bat4) < theshold) {
        break;

      }
      if (digitalRead(hbas) == 0) {
        break;
      }
    }
    //charging


    if (analogRead(bat1) < theshold2 and analogRead(bat2) < theshold2 and analogRead(bat3) < theshold2 and analogRead(bat4) < theshold2) {
      p1, p2, p3, p4 = 0;
      Serial.println("Mode7");
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }

    if (analogRead(bat1) >= theshold2 && analogRead(bat2) < theshold2 && analogRead(bat3) < theshold2 && analogRead(bat4) < theshold2) {
      p2, p3, p4 = 0;
      p1 = 1;
      Serial.println("Mode8");
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }

    if (analogRead(bat1) >= theshold2 && analogRead(bat2) >= theshold2 && analogRead(bat3) < theshold2 && analogRead(bat4) < theshold2) {
      p3, p4 = 0;
      p1, p2 = 1;
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      Serial.println("Mode9");
    }
    if (analogRead(bat1) >= theshold2 && analogRead(bat2) >= theshold2 && analogRead(bat3) >= theshold2 && analogRead(bat4) < theshold2) {
      p1, p2, p3 = 1;
      p4 = 0;
      Serial.println("Mode10");
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      asd = 0;

    }
    if (analogRead(bat1) >= theshold2 and analogRead(bat2) and theshold2 and analogRead(bat3) >= theshold2 && analogRead(bat4) >= theshold2) {
      p1, p2, p3, p4 = 1;
      Serial.println("Mode11");
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      asd = 1;
    }
    if (analogRead(bat1) < theshold2 or analogRead(bat2) < theshold2 or analogRead(bat3) < theshold2 or analogRead(bat4) < theshold2) {
      discharge = 0;

    }
    else {
      discharge = 1;
    }

  }

}
