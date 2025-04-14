#include <Arduino.h>
#include <ESP8266WiFi.h>

// Set up access point credentials
const char *ssid = "ESP8266-LED";  // Wi-Fi Name
const char *password = "12345678"; // Wi-Fi Password (min 8 chars)

// Set the onboard LED pin
const int ledPin = 2; // D4 on NodeMCU is GPIO2 (active LOW)

// Create server on port 80
WiFiServer server(80);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Turn OFF initially (active LOW)

  // Start the access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started!");
  Serial.print("Connect to: "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("Client connected!");
  while (!client.available()) {
    delay(1);
  }

  // Read HTTP request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // LED control logic
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, LOW); // Turn ON (active LOW)
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, HIGH); // Turn OFF
  }

  // Webpage HTML
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body{font-family:sans-serif;text-align:center;}button{padding:16px;font-size:20px;}</style></head>";
  html += "<body><h2>ESP8266 LED Control</h2>";
  html += "<p><a href=\"/LED=ON\"><button>Turn ON</button></a></p>";
  html += "<p><a href=\"/LED=OFF\"><button>Turn OFF</button></a></p>";
  html += "</body></html>";

  // Send response
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
  client.print(html);

  delay(1);
  Serial.println("Client disconnected");
}
