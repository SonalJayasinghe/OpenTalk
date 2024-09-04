#include <OpenTalk.h>

// You need to install ArduinoJson library
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "<Your WIFI SSID>";
const char* password = "<Your WIFI Password>";
const char* openAiKey = "<Your OpenAI Key>";

// Initialize OpenTalk
OpenTalk myTalk(ssid, password);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // Connect to WiFi network
  myTalk.connectToWiFi();  
}


void loop() {
  
  if(Serial.available() > 0){

    // Read user input
    String content = Serial.readStringUntil('\n');
    Serial.println("User: " + content);

    // Call OpenAI Chat Completion
    // The model parameter can be "gpt-4o", "gpt-4", "gpt-3.5-turbo", "gpt-3.5...."
    String response = myTalk.openAIChatCompletion(openAiKey, "gpt-4o", content.c_str());

    // Handle the response
    outputHandler(response);
  }
}

void outputHandler(String response){
  if (response.length() > 0) {

        // Parse the JSON response
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, response);

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.f_str());
            return;
        }
        
        // Get the message content
        String messageContent = doc["choices"][0]["message"]["content"].as<String>();
        Serial.println("Assistant: " + messageContent);
    }
}


