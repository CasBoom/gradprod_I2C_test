/*
Read the temperature from an LM75-derived temperature sensor, and display it
in Celcius every 250ms. Any LM75-derived temperature should work.
*/

#include <Temperature_LM75_Derived.h>
#include "Wire.h"
#include "I2C_eeprom.h"

I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC64);

uint32_t start, dur1, dur2;
// The Generic_LM75 class will provide 9-bit (±0.5°C) temperature for any
// LM75-derived sensor. More specific classes may provide better resolution.
Generic_LM75 temperature;

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

void loop() {
  Serial.print("Temperature: ");
  Serial.print(temperature.readTemperatureC());
  Serial.println(" C");
  delay(1000);
}