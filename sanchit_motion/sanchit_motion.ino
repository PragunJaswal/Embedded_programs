const int SPin = D5;     // the number of the pushbutton pin
const int led1 =  D1;  // the number of the LED pin
const int led2 =  D2;
const int buzzer =  D3;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(SPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  
  buttonState = digitalRead(SPin);
Serial.println(buttonState);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
     digitalWrite(buzzer, HIGH);
  } else {
    // turn LED off:
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
     digitalWrite(buzzer, LOW);
  }
}
