#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5  // ESP32 pin GIOP5 
#define RST_PIN 27 // ESP32 pin GIOP27 

const char * ssid = "Josue";//nombre de red
const char * password = "unjeilitook";//contraseña de la red

const String serverName = "http://192.168.43.101/esp32/guarda_rfid.php";

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
        WiFiClient client;
        HTTPClient http;

        int rndNum = random(0,100);

        String rfid = "XXXXXXXXXXXX";

        String serverData = serverName;

        http.begin(client, serverData);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String httpRequestData = "rfid=" + rfid;
        int httpResponseCode = http.POST(httpRequestData);

        if (httpResponseCode>0){
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            Serial.println(http.getString());//payload
        } else {
            Serial.print("Error code");
            Serial.println(httpResponseCode);
        }
        
        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
    delay(5000);
}