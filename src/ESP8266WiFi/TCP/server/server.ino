// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "ESP8266WiFi.h"

#define NETWORK_NAME "ESP8266"
#define NETWORK_PASS "secure password"

#define TCP_SERVER_PORT 2000
#define TCP_CLIENT_TIMEOUT 30000 // 30 seconds inactivity timeout

WiFiServer server(TCP_SERVER_PORT);

unsigned long lastClientActivity = 0;

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
  server.begin();
  server.setNoDelay(true); //Do not wait for big packet to send

  Serial.println("Server started");
}

void loop()
{
  WiFiClient client;

  Serial.print("Waiting connections");

  do {
    client = server.available();

    Serial.print(".");
    delay(1000);
  } while (!client);

  Serial.println(" (done)");

  while (client.connected()) {
    if (client.available() > 0) {
      lastClientActivity = millis();

      String text = client.readString();
      Serial.println("Received from the client: " + text);

      client.flush();

      // Send a message back to the client
      Serial.print("Sending a message to the client... ");
      client.println("Hello from ESP8266");
      Serial.println("(done)");
    }

    // Check for client timeouts
    if (lastClientActivity > 0 && lastClientActivity + TCP_CLIENT_TIMEOUT < millis()) {
      break;
    }
  }

  Serial.print("Client disconnecting... ");
  client.stop();
  Serial.println("(done)");
}
