// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "ESP8266WiFi.h"
#include <WiFiUdp.h>

#define NETWORK_NAME "network-name"
#define NETWORK_PASS "network-pass"

#define UDP_SERVER_IP "192.168.1.46"
#define UDP_SERVER_PORT 2000

WiFiUDP client;

void setup()
{
  // Begin serial communication with the host computer
  Serial.begin(115200);
  Serial.println();

  // Wait
  delay(1000);

  // Begin wireless communication with the network
  WiFi.begin(NETWORK_NAME, NETWORK_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" (done)");

  // Successfully connected
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Serial.print("Sending a message to the host... ");
  client.beginPacket(UDP_SERVER_IP, UDP_SERVER_PORT);
  client.println("Hello from the client");
  client.endPacket();
  Serial.println("(done)");

  delay(5000);
}
