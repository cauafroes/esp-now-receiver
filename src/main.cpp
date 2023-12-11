#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct message {
   int red;
   int green;
} message;
message myMessage;

#define MOT_A1_PIN 13
#define MOT_A2_PIN 15

void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}

void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  //  Serial.println("hello");
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  Serial.print("Red:");
  Serial.println(myMessage.red); 
  Serial.print("Green:");
  Serial.println(myMessage.green);
}
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
  WiFi.mode(WIFI_STA);

  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  
  //CONFIGURE MOTORS
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);

  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
}

void loop(void)
{
  // set_motor_pwm(255, MOT_A1_PIN, MOT_A2_PIN);
}