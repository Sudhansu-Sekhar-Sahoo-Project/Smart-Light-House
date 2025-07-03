#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// ✅ Replace these with your actual Wi-Fi credentials
const char* ssid = "Sudhansu's Pixel";
const char* password = "123123123";

ESP8266WebServer server(80);

// ✅ Relay pin connections
#define RELAY1 D1   // IN1 of Relay
#define RELAY2 D2   // IN2 of Relay

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // ✅ Register this ESP IP to your Spring Boot backend
  if (WiFi.status() == WL_CONNECTED) {
  HTTPClient http;
  WiFiClient client;
  http.begin(client, "http://10.227.63.239:8080/register-ip?ip=" + WiFi.localIP().toString()); // ✅ Fixed
  http.GET();
  http.end();
}


  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  server.on("/bulb1/on", []() {
    digitalWrite(RELAY1, HIGH);
    server.send(200, "text/plain", "Bulb 1 ON");
  });

  server.on("/bulb1/off", []() {
    digitalWrite(RELAY1, LOW);
    server.send(200, "text/plain", "Bulb 1 OFF");
  });

  server.on("/bulb2/on", []() {
    digitalWrite(RELAY2, HIGH);
    server.send(200, "text/plain", "Bulb 2 ON");
  });

  server.on("/bulb2/off", []() {
    digitalWrite(RELAY2, LOW);
    server.send(200, "text/plain", "Bulb 2 OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
