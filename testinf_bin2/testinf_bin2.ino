const int trig = D3;
const int echo = D4;
const int trig1 = D7;
const int echo1 = D2;
const int trig2 = D5;
const int echo2 = D6;
long durat;
int distance;
int bin = 0;
long durat1;
int distance1;
int bin1 = 0;
long durat2;
int distance2;
int bin2 = 0;

void setup(){
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT_PULLUP);
    pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT_PULLUP);
    pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT_PULLUP);
}

void loop() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    durat = pulseIn(echo, HIGH);
    distance = durat * 0.034 / 2;
    Serial.println(distance);        //Uncomment to measure distance of bin
    bin=map(distance, 25, 0, 0,100);
//    Serial.println(bin);
    delay(200);

//    digitalWrite(trig1, LOW);
//    delayMicroseconds(2);
//    digitalWrite(trig1, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trig1, LOW);
    
    
//            //Uncomment to measure distance of bin
//    bin1=map(distance1, 26, 0, 0,100);
////    Serial.println(bin1);
//    delay(200);

    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);
    durat1 = pulseIn(echo1, HIGH);
    durat2 = pulseIn(echo2, HIGH);
    distance1 = durat1 * 0.034 / 2;
    distance2 = durat2 * 0.034 / 2;
    Serial.println(distance1);
    Serial.println(distance2);
    delay(200);
 
}
