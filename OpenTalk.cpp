#include "OpenTalk.h"

OpenTalk::OpenTalk(const char* ssid, const char* password) {
    _ssid = ssid;
    _password = password;
}

//Connecting to Wifi
void OpenTalk::connectToWiFi() {
    WiFi.begin(_ssid, _password);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected to the WiFi network");
}

//OpenAI Chat Completion
String OpenTalk::openAIChatCompletion(const char* openAIKey, const char* model, const char* content){

    //Check if connected to the internet
    if(Wifi.status() != WL_CONNECTED){
        Serial.println("No Internet - OpenAI Chat Completion failed");
        return;
    }

    HTTPClient http;
    String response;

    http.begin("https://api.openai.com/v1/chat/completions"); //OpenAI Chat Completion Endpoint
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(openAIKey)); //OpenAI API Key

    String json = "{"
                        "\"model\": \"" + String(model) + "\","
                         "\"messages\": ["
                         "{"
                            "\"role\": \"user\","
                            "\"content\": \"" + String(content) + "\""
                         "}"
                        "]"
                    "}";

    //Send the POST request
    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {
        response = http.getString();
    } else {
        response = "Error on sending POST: " + String(httpResponseCode);
    }

    http.end();
    return response;
}