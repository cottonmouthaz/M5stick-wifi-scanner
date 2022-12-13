#include <Arduino.h>
#include <WiFi.h>
#include <M5Unified.h>

// the setup routine runs once when M5Stack starts up
void setup(){

    // Initialize the M5Stack object
    M5.begin();
    Serial.begin(115200);
    // LCD display
    M5.Lcd.printf("Wi-Fi SSID Scanner");
    Serial.println("Wi-Fi SSID Scanner");

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

}

// the loop routine runs over and over again forever
void loop() {

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    if (n == 0) {
        M5.Lcd.println("No networks found");
        Serial.println("No networks found");
    } else {
        M5.Lcd.print(n);
        M5.Lcd.println("Networks found");
        Serial.println("Networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            M5.Lcd.print(i + 1);
            M5.Lcd.print(": ");
            M5.Lcd.print(WiFi.SSID(i));
            M5.Lcd.print(" ");
            M5.Lcd.print(WiFi.channel(i));
            M5.Lcd.print("CH");
            M5.Lcd.print(" (");
            M5.Lcd.print(WiFi.RSSI(i));
            M5.Lcd.print(")");
            M5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");

            // Serial Monitor
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" ");
            Serial.print(WiFi.channel(i));
            Serial.print("CH");
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));   // Received Signal Strength Indicator(RSSI) is a measurement of the power present in a received radio signal
            Serial.print(") ");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
//            Serial.print("BSSID: ");
//            Serial.println(WiFi.BSSID(i));
            delay(10);
        }
    }

    // Wait a bit before scanning again
    delay(5000);
}