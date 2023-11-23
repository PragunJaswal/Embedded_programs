#include<Wire.h>

const int MPU_addr1 = 0x68; //First MPU6050 I2C address
const int MPU_addr2 = 0x69; // Second MPU6050 I2C address

int16_t AcX1, AcY1, AcZ1, Tmp1, GyX1, GyY1, GyZ1;
int16_t AcX2, AcY2, AcZ2, Tmp2, GyX2, GyY2, GyZ2;

int minVal = 265;
int maxVal = 402;

double x1, y1, z1;
double x2, y2, z2;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr2);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(9600);
  Serial.println("Sensor 1 - X, Sensor 1 - Y, Sensor 1 - Z, Sensor 2 - X, Sensor 2 - Y, Sensor 2 - Z");
}

void loop() {
  // Read data from the first sensor (0x68)
  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr1, 14, true);
  AcX1 = Wire.read() << 8 | Wire.read();
  AcY1 = Wire.read() << 8 | Wire.read();
  AcZ1 = Wire.read() << 8 | Wire.read();
  
  // Read data from the second sensor (0x69)
  Wire.beginTransmission(MPU_addr2);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr2, 14, true);
  AcX2 = Wire.read() << 8 | Wire.read();
  AcY2 = Wire.read() << 8 | Wire.read();
  AcZ2 = Wire.read() << 8 | Wire.read();


  int xAng2 = map(AcX2, minVal, maxVal, -90, 90);
  int yAng2 = map(AcY2, minVal, maxVal, -90, 90);
  int zAng2 = map(AcZ2, minVal, maxVal, -90, 90);

  x2 = RAD_TO_DEG * (atan2(-yAng2, -zAng2) + PI);
  y2 = RAD_TO_DEG * (atan2(-xAng2, -zAng2) + PI);
  z2 = RAD_TO_DEG * (atan2(-yAng2, -xAng2) + PI);

  // Serial.println("Sensor 2:");
  // Serial.print("AngleX= ");
  // Serial.println(x2);
  // Serial.print("AngleY= ");
  // Serial.println(y2);
  // Serial.print("AngleZ= ");
  // Serial.println(z2);


  Serial.print(x2);
  Serial.print(", ");
  Serial.print(y2);
  Serial.print(", ");
  Serial.println(z2);
  delay(400);
}
