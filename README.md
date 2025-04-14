# `ArduinoIDE` & `PlatformIO` setup
> also this repo has a `PlatformIO project`
---

# ArduinoIDE
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

---

</br>
</br>

<div style="display: flex; align-items: center; gap: 10px;" align="center">
  
## ⭐ Projects ⭐
</div>

[![Screenshot_14-4-2025_163550_www youtube com](https://github.com/user-attachments/assets/974a1c49-8330-44cc-a3c7-a4a4a382c108)](https://www.youtube.com/playlist?list=PL_RecMEcs_p-5UwLqFBFtat90L8IOc1bZ)

---

# for Pro Users

Welcome to **PlatformIO** — it's a powerful extension for **Visual Studio Code** that offers a modern and more professional workflow for embedded development (like ESP8266). If you are good to using the Arduino IDE, you’ll find some things familiar, and others a bit new but more flexible.

---

## ✅ **Step-by-Step Guide: Setup PlatformIO in VS Code (for ESP8266)**

---

### 🧰 **1. Install Visual Studio Code (VS Code)**

If you haven't already:
- Download from: [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Install it like any other app.

---

### ⚙️ **2. Install the PlatformIO Extension**

1. Open **VS Code**.
2. Go to **Extensions** (`Ctrl + Shift + X`).
3. Search for **PlatformIO IDE**.
4. Click **Install**.

> 💡 This will also install Python if it's not already installed (required by PlatformIO).

<p align="center">
  <img src="https://github.com/user-attachments/assets/d9084ff5-916f-4c7b-8232-5ac7de26b708" alt="Image 1" width="46%" style="margin-right: 10px;"/>
  <img src="https://github.com/user-attachments/assets/fdc4c02c-5eec-4f1f-8bb1-6cbb274cf2ef" alt="Image 2" width="46%" style="margin-right: 10px;"/>
</p>

![Screenshot 2025-04-15 014729](https://github.com/user-attachments/assets/2a43a2d2-5864-4a8d-99ce-44b6aef4339f)

---

### 🌐 **3. Create a New Project in PlatformIO**

1. Click on the **PlatformIO alien icon 🛸** in the left sidebar.
2. Click **"New Project"**.
3. Fill in:
   - **Name:** `ESP8266_LED_Control`
   - **Board:** Search and select `NodeMCU 1.0 (ESP-12E Module)`
   - **Framework:** Select `Arduino`
   - Leave location as default.
4. Click **"Finish"**.

PlatformIO will now generate a project structure and install the necessary platform files.

<p align="center">
  <img src="https://github.com/user-attachments/assets/396503f1-4709-4d13-896f-d9d2855367e2" alt="Image 1" width="46%" style="margin-right: 10px;"/>
  <img src="https://github.com/user-attachments/assets/e0253702-ee6c-4a1e-b1c9-3bbb77f2e136" alt="Image 2" width="46%" style="margin-right: 10px;"/>
</p>

---

### 📁 **4. Understand the Project Structure**

Here's what PlatformIO creates:

```
ESP8266_LED_Control/
├── include/       → Header files (.h)
├── lib/           → Custom libraries
├── src/           → Your main code (like Arduino .ino files)
│   └── main.cpp   → Your main code file
├── platformio.ini → Project config file
```

![Screenshot (285)](https://github.com/user-attachments/assets/f9647056-1d57-4d1e-825c-00d0993785f0)

---

### 📝 **5. Write Your Code**

Open `src/main.cpp` and paste your existing code there.

**PlatformIO uses `.cpp` files**, so wrap your Arduino code like this:

```cpp
#include <Arduino.h>
#include <ESP8266WiFi.h>

// Your existing code...
```

Also, make sure `setup()` and `loop()` are present and not inside a class or function.

---

### ⚙️ **6. Update platformio.ini (Optional but Recommended)**

Open `platformio.ini` and ensure it looks like this:

```ini
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
monitor_speed = 115200
```

You can add more options later (like libraries, OTA, etc.).

---

### 🔌 **7. Connect & Upload to ESP8266**

1. Plug in your NodeMCU.
2. Hit **"Upload"** (checkmark/arrow icon in the bottom toolbar).
3. PlatformIO will:
   - Compile your code.
   - Upload it to your board.
   - Open the Serial Monitor (if you click the plug icon).

---

### 🔍 **8. Monitor Serial Output**

- To see your `Serial.println()` outputs:
  - Click the **"Monitor"** icon (plug symbol), or use shortcut `Ctrl + Alt + M`.

---

### 🧼 **9. Common Shortcuts**

| Task | Shortcut / Button |
|------|-------------------|
| Build | `Ctrl + Alt + B` |
| Upload | `Ctrl + Alt + U` |
| Monitor | `Ctrl + Alt + M` |
| Clean | `Ctrl + Alt + C` |

---

### 🧠 **10. Differences from Arduino IDE (Quick Tips)**

| Arduino IDE | PlatformIO |
|-------------|------------|
| `.ino` file | `.cpp` with `setup()` & `loop()` |
| Sketchbook folder | Full project structure |
| Libraries added via Library Manager | Use `lib_deps` in `platformio.ini` |
| Serial Monitor | Built-in, customizable |

---

![Screenshot (286)](https://github.com/user-attachments/assets/4c1b3f52-ecb6-467e-95d7-dc3e20436ab4)

### code for PlatformIO

```cpp
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
```

![Screenshot (290)](https://github.com/user-attachments/assets/69f042e1-b6a8-4eda-a7f3-80e4f8e8ebff)
![Screenshot (292)](https://github.com/user-attachments/assets/ec1f6e4d-4f74-473d-9acf-1237d4b6b5c6)

## update for ESP 32
> see the main code in the `src` & `platformio.ini` and I can maintion all changes.

Absolutely! Here's what you need to change when moving your project from **ESP8266** to **ESP32 (ESP-WROOM-32)**:

---

### 🔧 1. **Change the `platformio.ini` file**

Replace:
```ini
[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino
```

With:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

---

### 🔧 2. **Update GPIO Pin Numbers in Code**

If you were using pins like `D1`, `D2`, etc. on ESP8266, change them to ESP32 GPIOs.

For example:

#### ✅ Before (for ESP8266):
```cpp
#define FRONT_LED D1
#define BACK_LED  D2
#define LEFT_LED  D3
#define RIGHT_LED D4
```

#### 🔁 After (for ESP32):
Replace them with real GPIO numbers:
```cpp
#define FRONT_LED 18
#define BACK_LED  19
#define LEFT_LED  21
#define RIGHT_LED 22
```

> 🧠 You can use any GPIOs like 2, 4, 5, 18, 19, 21, 22, 23 — just avoid pins like 6–11 (used for flash).

---

### 🔧 3. **No Change Needed for `setup()` and `loop()`**

Your usual Arduino code stays the same:
```cpp
void setup() {
  pinMode(FRONT_LED, OUTPUT);
  pinMode(BACK_LED, OUTPUT);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
}

void loop() {
  digitalWrite(FRONT_LED, HIGH);
  delay(1000);
  digitalWrite(FRONT_LED, LOW);
  delay(1000);
}
```
---

### complete Updated Code

<details>
  
```cpp
#include <Arduino.h>
// #include <ESP8266WiFi.h>
#include <WiFi.h> // Use this for ESP32

// Set up access point credentials
const char *ssid = "ESP8266-LED";  // Wi-Fi Name
const char *password = "12345678"; // Wi-Fi Password (min 8 chars)

// Set the onboard LED pin
const int ledPin = 2; // D4 on NodeMCU is GPIO2 (active LOW) & GPIO2 is commonly onboard LED in ESP32 also

// Create server on port 80
WiFiServer server(80);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, HIGH); // Turn OFF initially (active LOW)
  digitalWrite(ledPin, LOW); // ESP32 onboard LED usually active HIGH

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
    // digitalWrite(ledPin, LOW); // Turn ON (active LOW) ESP 8266
    digitalWrite(ledPin, HIGH); // Turn ON (active HIGH on ESP32)
  }
  if (request.indexOf("/LED=OFF") != -1) {
    // digitalWrite(ledPin, HIGH); // Turn OFF - 8266
    digitalWrite(ledPin, LOW); // Turn OFF - ESP32
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

</details>

---

<p align="center">
  <img src="https://github.com/user-attachments/assets/f53fe305-77ce-4d1a-a1a7-6438eefc689d" alt="Image 1" width="46%" style="margin-right: 10px;"/>
  <img src="https://github.com/user-attachments/assets/021351bc-84c5-4960-b190-92cbbde977b4" alt="Image 2" width="46%" style="margin-right: 10px;"/>
</p>

How to **see the IP address** of ESP-WROOM-32 (Access Point mode) after uploading the code:

---

### 🔍 Steps to View IP Address in PlatformIO Serial Monitor:

1. **Open the Serial Monitor**:
   - Click the **"plug" icon** 🔌 at the bottom bar of VS Code (or go to **Terminal > New Terminal** and run):
     ```
     pio device monitor
     ```
   - Or use the shortcut: `Ctrl + Alt + M` (Windows/Linux) or `Cmd + Alt + M` (Mac).

2. **Wait for Boot Logs**:
   - After uploading, the ESP32 reboots and prints messages like:
     ```
     Access Point Started!
     Connect to: ESP32-LED
     IP address: 192.168.4.1
     ```

3. **Connect to Wi-Fi on Phone/Laptop**:
   - Go to Wi-Fi settings on your phone/laptop.
   - Connect to the Wi-Fi network: `ESP32-LED` with password `12345678`.

4. **Open Browser**:
   - In the browser, go to: [http://192.168.4.1](http://192.168.4.1)

---

### 🧠 Tip:
If the Serial Monitor is not showing any output, make sure:
- You have `Serial.begin(115200);` in your code (you do ✅).
- `monitor_speed = 115200` is set correctly in your `platformio.ini`.
- You don’t have multiple monitors open.

![Screenshot (295)](https://github.com/user-attachments/assets/1e85d961-4b5b-4096-a04b-73866d723596)
