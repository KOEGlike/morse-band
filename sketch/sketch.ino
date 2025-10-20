


#include <WiFi.h>
#include <esp_now.h>

//58:8C:81:B0:3B:A0
//58:8C:81:AF:FB:4C
const int BUTTON_PIN = 8;
const int MOTOR_PIN = 10;

// --- CHANGE THIS to the MAC of the other board ---
//uint8_t peerAddress[] = {0x58, 0x8C, 0x81, 0xAF, 0xFB, 0x4C}; // example
uint8_t peerAddress[] = {0x58, 0x8C, 0x81, 0xB0, 0x3B, 0xA0}; // example

typedef struct struct_message {
  bool buttonPressed;
} struct_message;

struct_message outgoingMessage;
struct_message incomingMessage;

// --- Updated ESP-NOW v5.x callbacks ---
void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  // optional debug
}

void onDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  digitalWrite(MOTOR_PIN, incomingMessage.buttonPressed ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  WiFi.mode(WIFI_STA);

  Serial.print("My MAC address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(onDataSent);
  esp_now_register_recv_cb(onDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);

  Serial.println("Ready!");
}

void loop() {
  static unsigned long lastSend = 0;
  static bool lastButton = HIGH;

  bool currentButton = digitalRead(BUTTON_PIN);
  bool pressed = (currentButton == LOW); // since INPUT_PULLUP

  // Send every 50 ms or when state changes
  if (millis() - lastSend > 50 || pressed != lastButton) {
    outgoingMessage.buttonPressed = pressed;
    esp_now_send(peerAddress, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));
    lastSend = millis();
    lastButton = pressed;
  }
}