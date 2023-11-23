float calibration_value = 16.12   //calibrated values
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
#define Pin 12
float ph_act;
 
void setup() 
{
 Serial.begin(9600);

}
void loop() {
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=map(analogRead(34), 0, 4096, 4096, 0);
 Serial.println(buffer_arr[i]);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }  
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*3.3/4096.0/6;  
 //Serial.print("Voltage: ");
 //Serial.println(volt);

// float calibration_value = mapf(analogRead(Pin), 0, 4096, 16.00, 27.12);
// Serial.print("Cal value");
// Serial.println(calibration_value);


  ph_act = -5.70 * volt + calibration_value;
 
 Serial.print("pH Val: ");
 Serial.println(ph_act);
 delay(1000);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
