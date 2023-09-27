#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct message {
   int red;
   int green;
} message;
message myMessage;

void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  //  Serial.println("Message received.");
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  // Serial.print("Red:");
  // Serial.println(myMessage.red); 
  // Serial.print("Green:");
  // Serial.println(myMessage.green);
}
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
  WiFi.mode(WIFI_STA);

  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");
  
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
}
void loop() {
  // put your main code here, to run repeatedly:
}