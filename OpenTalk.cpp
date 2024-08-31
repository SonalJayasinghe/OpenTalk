#include "OpenTalk.h"

OpenTalk::OpenTalk(const char* ssid, const char* password) {
    _ssid = ssid;
    _password = password;
}

void OpenTalk::connectToWiFi() {
    WiFi.begin(_ssid, _password);
    Serial.println("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to the WiFi network");
}