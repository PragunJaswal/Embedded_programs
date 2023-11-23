#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
sensors.begin();
}

void loop() {

  Serial.println(sensors.getDeviceCount());
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.println(".");  // for debugging purpose
  Serial.println(temp);
delay(100);
}
