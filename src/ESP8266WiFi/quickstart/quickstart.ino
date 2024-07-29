// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "ESP8266WiFi.h"

#define NETWORK_NAME "network-name"
#define NETWORK_PASS "network-pass"

void setup()
{
  // Begin serial communication with the host computer
  Serial.begin(115200);
  Serial.println();

  //Wait
  delay(500);

  // Begin wireless communication with the network
  WiFi.begin(NETWORK_NAME, NETWORK_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Successfully connected
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Your loop code
}
