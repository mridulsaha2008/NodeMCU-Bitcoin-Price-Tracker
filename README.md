# IoT Bitcoin Price Ticker (ESP8266 + I2C LCD)

An internet-of-things (IoT) live dashboard tracking system that uses an **ESP8266 Wi-Fi module** to securely fetch live cryptocurrency financial data from the CryptoCompare API and display the live price of Bitcoin (BTC) in Indian Rupees (INR) on an I2C-enabled 16x2 LCD screen.

---

## 🚀 Features

- **Live Crypto Tracking:** Polls the CryptoCompare REST API securely over HTTPS (`Port 443`) to get real-time price rates.
- **Dynamic JSON Parsing:** Uses the `ArduinoJson` memory management library to read and unpack the network payload buffer dynamically.
- **Robust Connection Handshaking:** Features visual display notifications tracking local Wi-Fi connection states and API connection status.
- **I2C Multiplexing:** Reduces the wiring overhead to just two data connections (SDA/SCL) using an I2C hardware module backpack interface.

---

## 🛠️ Hardware Requirements

* **ESP8266 Board** (NodeMCU or WeMos D1 Mini) - 1x
* **16x2 LCD Screen** with attached **I2C Backpack module** (PCF8574) - 1x
* Jumper wires & USB Power cable

---

## 📌 Schematic Wiring Matrix

The I2C protocol allows the display to be driven with minimal pins. Wire your ESP8266 module to the I2C LCD board interface using the following configurations:

| I2C LCD Pin | ESP8266 Pin | Pin Description |
| :---: | :---: | :--- |
| **VCC** | **VIN / 5V** | 5V Power Supply for LCD Driver and Backlight |
| **GND** | **GND** | Ground Plane Reference |
| **SDA** | **D1** | I2C Data Stream Communication Line |
| **SCL** | **D2** | I2C Hardware Clock Synchronization Line |

---

## ⚙️ Software Dependencies

Before compiling, make sure you have the following third-party libraries installed inside your **Arduino IDE Library Manager**:

1. **LiquidCrystal_I2C** by Frank de Brabander (Handles alphanumeric output control over I2C).
2. **ArduinoJson** by Benoit Blanchon (Optimized parsing engine for the API's payload object structure).

---

## 💻 Installation & Setup

1. Clone or download this repository onto your computer.
2. Open `Bitcoin_Price_on_LCD.ino` within the Arduino IDE.
3. Update the Wi-Fi credentials blocks to match your specific router access point:
   ```cpp
   const char* ssid     = "Your_Wi-Fi_SSID";
   const char* password = "Your_Wi-Fi_Password";
   ```

   ---

## ⚡ Stream-Based HTTP Parsing (Preventing Data Splitting)

Older revisions of raw TCP data fetching relied on rigid, hardcoded string slicing methods like `jsonPayload.substring(555);`. Because modern web servers deliver packets dynamically and change HTTP header lengths on the fly, a fixed character offset causes the string to split or crop mid-data, leading to constant JSON deserialization failures.

---

## 🛠️ Hardware Matrix Troubleshooting

* **Garbled Characters on Display:** If your LCD panel powers on but outputs meaningless blocks or broken symbols, verify your I2C bus device address. While `0x27` is standard for most PCF8574 backpacks, some variations are hardwired to `0x3F`. You can find your exact device address by running a generic I2C scanner sketch.  
* **Faint or Invisible Text:** If the backlight turns on but no alphanumeric text appears, find the small blue potentiometer on the rear face of the I2C backpack module. Use a small screwdriver to turn it slowly until the characters contrast clearly against the screen background.
* **Network Handshake Failures:** Ensure your local access point supports a clear connection route to port `443`. The script calls `client.setInsecure();` to bypass strict SSL root certificate chain validation (which saves precious heap memory on the ESP8266 architecture), but it still requires a clear internet gateway to complete its TCP handshake.
* **API Rate Limiting & HTTP 429:** Aggressive polling of the CryptoCompare API without an API key can trigger temporary IP bans or rate-limit responses (`HTTP/429 Too Many Requests`). This alters the body structure returned from the host server. Ensure the program incorporates a generous execution delay (e.g., `delay(10000);` or greater) between consecutive network calls to respect the remote host's data constraints.

---

## 🛡️ License

Developed with ❤️ for real-time crypto telemetry tracking.
