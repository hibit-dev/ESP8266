// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "ESP8266WiFi.h"

#define NETWORK_NAME "network-name"
#define NETWORK_PASS "network-pass"

#define TCP_SERVER_IP "192.168.1.46"
#define TCP_SERVER_PORT 2000

WiFiClient client;

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
  Serial.print("Connecting to the host");

  do {
    Serial.print(".");
    delay(1000);
  } while (!client.connect(TCP_SERVER_IP, TCP_SERVER_PORT));

  Serial.println(" (done)");

  Serial.print("Sending a message to the host... ");
  client.println("Hello from the client");
  Serial.println("(done)");

  while (client.connected()) {
    if (client.available() > 0) {
      String text = client.readString();
      Serial.println("Received from the host: " + text);
    }
  }

  Serial.print("Disconnecting... ");
  client.stop();
  Serial.println("(done)");

  delay(5000);
}
