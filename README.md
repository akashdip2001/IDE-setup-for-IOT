# Arduino-IDE-setup

## Prefecences

![Screenshot (272)](https://github.com/user-attachments/assets/cd101243-bd42-4cbd-9259-71a12630a777)

</br>

- ESP8266 https://arduino.esp8266.com/stable/package_esp8266com_index.json
- ESP 32 https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
- Pico W https://github.com/earlephilhower/arduino-pico/releases/latest/download/package_rp2040_index.json

</br>
</br>

![Screenshot (273)](https://github.com/user-attachments/assets/d9dd2a10-e79f-4bef-afcd-631eebed37fa)
![Screenshot (275)](https://github.com/user-attachments/assets/5a43d700-49af-4468-a1cb-8ccd059123ba)

<p align="center">
  <img src="https://github.com/user-attachments/assets/9d04b7c6-b7ab-4050-a623-08bd9b39c024" alt="Image 1" width="59%" style="margin-right: 10px;"/>
  <img src="https://github.com/user-attachments/assets/d2f24215-948f-4188-9686-82ea9372539d" alt="Image 2" width="33%" style="margin-right: 10px;"/>
</p>

![Screenshot (277)](https://github.com/user-attachments/assets/4c859f09-b17c-4c9a-8ef7-77462869dc9a)


---


## SAMPLE CODE

Here's the simple code for **ESP8266 NodeMCU** as a **Wi-Fi Access Point**, hosts a **web interface**, and **toggle the onboard LED (D4 / GPIO2)** from mobile browser.

---

## 🔧 Hardware Required:
- ESP8266 NodeMCU
- Micro USB cable
- Mobile or laptop with Wi-Fi

---

## ✅ Code: ESP8266 Web Interface as Access Point (LED Control)

```cpp
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
```

---

## 📱 How to Use:
1. **Upload the code** to your ESP8266 using Arduino IDE.
2. Open **Serial Monitor** @ 115200 baud to see debug info.
3. On your mobile or PC:
   - Go to Wi-Fi settings
   - Connect to `ESP8266-LED` (password: `12345678`)
4. Open a browser and visit `192.168.4.1`
5. Click **"Turn ON"** or **"Turn OFF"** to control the onboard LED.
