// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "SoftwareSerial.h"

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial SerialEsp(RX_PIN, TX_PIN);

void setup()
{
  // Begin serial communication with the host computer
  Serial.begin(115200);
  Serial.println("Remember to to set Both NL & CR in the serial monitor.");

  // Begin serial communication with the ESP8266 module
  SerialEsp.begin(115200);
  Serial.println("ESP8266 module is ready");
}

void loop()
{
  // We have available information to read
  if (SerialEsp.available()) {
    Serial.write(SerialEsp.read());
  }

  // We have available information to write
  if (Serial.available()) {
    SerialEsp.write(Serial.read());
  }
}
