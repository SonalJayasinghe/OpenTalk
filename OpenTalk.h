#ifndef OpenTalk_H
#define OpenTalk_H

#include <Arduino.h>
#include <WiFi.h>


class OpenTalk {
public:
    OpenTalk(const char* ssid, const char* password);
    void connectToWiFi();
    String openAIChatCompletion(const char* openAIKey, const char* model, const char* prompt);
    
private:
    const char* _ssid;
    const char* _password;
};

#endif