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
    Serial.println("");
    Serial.println("Connected to the WiFi network");
}

String OpenTalk::openAIChatCompletion(const char* openAIKey, const char* model, const char* content){
    HTTPClient http;
    String response;

    http.begin("https://api.openai.com/v1/chat/completions");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(openAIKey));

    String json = "{"
                        "\"model\": \"" + String(model) + "\","
                         "\"messages\": ["
                         "{"
                            "\"role\": \"user\","
                            "\"content\": \"" + String(content) + "\""
                         "}"
                        "]"
                    "}";

    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {
        response = http.getString();
    } else {
        response = "Error on sending POST: " + String(httpResponseCode);
    }

    http.end();
    return response;
}