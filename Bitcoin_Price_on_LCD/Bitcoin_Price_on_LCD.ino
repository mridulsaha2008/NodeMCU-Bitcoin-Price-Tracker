#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

int lcdAddress = 0x27;
LiquidCrystal_I2C lcd(lcdAddress, D1, D2);

const char* ssid = "iPhone 15 Pro Max";
const char* password = "rredf8smpc";
const char* host = "min-api.cryptocompare.com";
const int port = 443;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Connecting to ");
    lcd.print(ssid);
    lcd.print(".");
    delay(2000);
    lcd.clear();
  }

  lcd.setCursor(0, 0);
  lcd.print("Connected to ");
  lcd.print(ssid);
  lcd.print(".");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;

    client.setInsecure();

    if (client.connect(host, port)) {
      client.println("GET /data/price?fsym=BTC&tsyms=INR HTTP/1.1");
      client.println("Host: min-api.cryptocompare.com");
      client.println("Connection: close");
      client.println();
      }

      String jsonPayload = client.readString();
      jsonPayload = jsonPayload.substring(555);
      jsonPayload = jsonPayload.substring(0, jsonPayload.length() - 2);

      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, jsonPayload);

      if (error) {
        lcd.print("JSON parsing error: ");
        lcd.println(error.c_str());
        lcd.clear();
      } else {
        float bitcoinPrice = doc["INR"];
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bitcoin Price:");
        lcd.setCursor(0, 1);
        lcd.print("INR ");
        lcd.print(bitcoinPrice);
      }
      client.stop();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Connection error!!");
    }
  delay(1000);
}