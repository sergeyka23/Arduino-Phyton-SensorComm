#include <Wire.h>


uint8_t _address = 0x40;
  
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("HDC1080 Sergey Test");

Wire.begin(_address);

  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);

}

uint16_t readData(uint8_t pointer) {
  Wire.beginTransmission(_address);
  Wire.write(pointer);
  Wire.endTransmission();
  
  delay(9);
  Wire.requestFrom(_address, (uint8_t)2);

  byte msb = Wire.read();
  byte lsb = Wire.read();

  return msb << 8 | lsb;
}

double readTemperature() {
  uint16_t rawT = readData(0x00);
  return (rawT / pow(2, 16)) * 165.0 - 40.0;
}
double readHumidity() {
  uint16_t rawH = readData(0x01);
  return (rawH / pow(2, 16)) * 100.0;
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("T=");
Serial.println(readTemperature());
Serial.print("H=");
Serial.println(readHumidity());
delay(3000);
}
