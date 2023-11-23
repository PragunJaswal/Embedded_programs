String firstName;
const int x=10;
void setup() {
Serial.begin(9600);
x=20;
firstName= "Dinesh";
delay(1000);
Serial.println(x);
delay(1000);
firstName= "Dk";

}

void loop(){
Serial.println(firstName);
  

}
