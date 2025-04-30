//! \file


#include <Temperature_LM75_Derived.h>
#include "Wire.h"
#include "I2C_eeprom.h"

//! EEPROM object, taken the device size and address as inputs
I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC64);
//! LM75 sensor object, takes no arguments
Generic_LM75 temperature;

//! Sets up the program and checks the I2C EEPROM chip 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  ee.begin();
  if (! ee.isConnected())
  {
    Serial.println("No EEPROM, check address");
    Serial.println("Continuing temperature readout");
    delay(1000);
  } else {
    Serial.println("Clearing first 10 bytes");
    ee.setBlock(0, 0, 10);  //  clear first 100 bytes
    Serial.println("Reading first 10 bytes");
  for(int i = 0; i<10; i++){
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(ee.readByte(i));
  }

  Serial.println("Writing first 10 bytes");
  for (int i = 0; i < 10; i++)
  {
    ee.writeByte(i, i);
  }
  Serial.println("Reading first 10 bytes");
  for(int i = 0; i<10; i++){
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(ee.readByte(i));
  }

  Serial.println("done...");
  }
}

//! Constant loop that prints the temperature
void loop() {
  Serial.print("Temperature: ");
  Serial.print(temperature.readTemperatureC());
  Serial.println(" C");
  delay(1000);
}