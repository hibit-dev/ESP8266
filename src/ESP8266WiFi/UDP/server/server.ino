// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "ESP8266WiFi.h"
#include <WiFiUdp.h>

#define NETWORK_NAME "ESP8266"
#define NETWORK_PASS "secure password"

#define UDP_SERVER_PORT 2000

WiFiUDP server;

void setup()
{
  // Begin serial communication with the host computer
  Serial.begin(115200);
  Serial.println();

  // Wait
  delay(1000);

  // Setup soft-AP for communication
  const bool softAp = WiFi.softAP(NETWORK_NAME, NETWORK_PASS);

  Serial.print("Setting soft-AP... ");
  Serial.println(softAp ? "(done)" : "(failed)");

  Serial.println("IP address: " + WiFi.softAPIP().toString());

  // Configuring server
  server.begin(UDP_SERVER_PORT);

  Serial.println("Server started");
}

void loop()
{
  if (server.parsePacket() > 0) {
    String text = server.readString();
    Serial.println("Received from the client: " + text);

    // Send a message back to the client
    Serial.print("Sending a message to the client... ");
    server.beginPacket(server.remoteIP(), server.remotePort());
    server.println("Hello from ESP8266");
    server.endPacket();
    Serial.println("(done)");
  }
}
