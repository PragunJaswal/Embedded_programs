void setup(){
  
  Serial.begin(9600); // Start the communication 


  }

  void loop(){

int val = digitalRead(6);

Serial.println(val);
    
    }
