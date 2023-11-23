int in;

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  pinMode(13,OUTPUT);

}

void loop() {

  if (Serial.available()) {
    in= Serial.read();
    Serial.println(in);
      if(in == 25){
    digitalWrite(13,HIGH);
    Serial.print("on");
    }
      if(in == '6'){
    digitalWrite(13,LOW);
    Serial.print("off");
    
    }
  }


}
