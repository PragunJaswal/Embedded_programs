int R1= 10000; // Value of resistor for EC probe
int EC_Read = A0;
int ECPower = A5; //not used
int Temp_pin = A3;
float Temp_C; // Do not change
float Temp_F; // Do not change
float Temp1_Value = 0;
float Temp_Coef = 0.019; // You can leave as it is
/////////////////This part needs your attention during calibration only///////////////
float Calibration_PPM =1080 ; //Change to PPM reading measured with a separate meter
float K= 0.04; //You must change this constant once 
float PPM_Con=0.5; 
float CalibrationEC= (Calibration_PPM*2)/1000;
float Temperature;
float EC;
float EC_at_25;
int ppm;
float A_to_D= 0;
float Vin= 5;
float Vdrop= 0;
float R_Water;
float Value=0;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int ECvalue = 0;

int MQsensorPin = A1; 
int MQsensorValue = 0;
void setup()
{
Serial.begin(9600);
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Pulse Width scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

pinMode(EC_Read,INPUT);
pinMode(ECPower,OUTPUT);
pinMode(11,INPUT);


//////////////////////////////////////////////////////////////////////////////////////////
// Calibrate (); // After calibration put two forward slashes before this line of code
//////////////////////////////////////////////////////////////////////////////////////////
}
void loop()
{
  // Serial.println("waiting");
if(digitalRead(11) == HIGH){
  Serial.println("pressed");
  ECvalue = GetEC(); //Calls GetEC()

	redPW = getRedPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Green Pulse Width
	greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(200);

	// Read Blue Pulse Width
	bluePW = getBluePW();
	// Delay to stabilize sensor
	delay(200);
  MQsensorValue = analogRead(MQsensorPin);
 

	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);
  Serial.print("ppm = ");
	Serial.println(ECvalue);
  Serial.print("MQ sensor = ");
  Serial.println(MQsensorValue);

delay(5000); //Do not make this less than 6 sec (6000)
Serial.println("ready");
}
}


int GetEC()
{
int val;
double Temp;
val=analogRead(Temp_pin);
Temp = log(((10240000/val) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp);
Temp_C = Temp - 273.15; // Kelvin to Celsius
Temp_F = (Temp_C * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit
Temp1_Value = Temp_C;
Temperature = Temp_C;
digitalWrite(ECPower,HIGH);
A_to_D= analogRead(EC_Read);
A_to_D= analogRead(EC_Read);
digitalWrite(ECPower,LOW);
Vdrop= (Vin*A_to_D) / 1024.0;
R_Water = (Vdrop*R1) / (Vin-Vdrop);
EC = 1000/ (R_Water*K);
EC_at_25 = EC / (1+ Temp_Coef*(Temperature-25.0));
ppm=(EC_at_25)*(PPM_Con*1000);
// Serial.print(" EC: ");
// Serial.print(EC_at_25);
// Serial.print(" milliSiemens(mS/cm) ");
// Serial.print(ppm);
// Serial.print(" ppm ");
// Serial.print(Temperature);
// Serial.println(" *C ");
return ppm;
}
////////////////////////////////////////////////////////////////////////////////////
void Calibrate ()
{
Serial.println("Calibration routine started");
float Temperature_end=0;
float Temperature_begin=0;
int val;
double Temp;
val=analogRead(Temp_pin);

Temp = log(((10240000/val) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp);
Temp_C = Temp - 273.15; // Kelvin to Celsius
Temp_F = (Temp_C * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit
Temp1_Value = Temp_C;
Temperature_begin=Temp_C;
Value = 0;
int i=1;
while(i<=10){
digitalWrite(ECPower,HIGH);
A_to_D= analogRead(EC_Read);
A_to_D= analogRead(EC_Read);
digitalWrite(ECPower,LOW);
Value=Value+A_to_D;
i++;
delay(6000);
};
A_to_D=(Value/10);
val=analogRead(Temp_pin);
Temp = log(((10240000/val) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp);
Temp_C = Temp - 273.15; // Kelvin to Celsius
Temp_F = (Temp_C * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit
Temp1_Value = Temp_C;
Temperature_end=Temp_C;
EC =CalibrationEC*(1+(Temp_Coef*(Temperature_end-25.0)));
Vdrop= (((Vin)*(A_to_D))/1024.0);
R_Water=(Vdrop*R1)/(Vin-Vdrop);
float K_cal= 1000/(R_Water*EC);
Serial.print("Replace K in line 23 of code with K = ");
Serial.println(K_cal);
Serial.print("Temperature difference start to end were = ");
Temp_C=Temperature_end-Temperature_begin;
Serial.print(Temp_C);
Serial.println("*C");
Serial.println("Temperature difference start to end must be smaller than 0.15*C");
Serial.println("");
Calibrate ();
}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}