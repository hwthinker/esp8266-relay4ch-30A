#include <Arduino.h>

// Pin relay
#define RLY1 16
#define RLY2 14
#define RLY3 12
#define RLY4 13

// Pin button
#define BUTTON_PIN 4

// Interval waktu untuk setiap relay (ms)
const unsigned long interval = 500; // 500 ms
unsigned long previousMillis = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // debounce 50ms

// Variabel untuk melacak relay yang aktif
int currentRelay = 0;

// Array pin relay
int relayPins[] = {RLY1, RLY2, RLY3, RLY4};
const int numRelays = sizeof(relayPins) / sizeof(relayPins[0]);

// Status tombol sebelumnya
int lastButtonState = HIGH;
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);
  Serial.println("\nESP8266 GPIO Input & Relay Test");
  
  // Setup pin button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Konfigurasi pin relay sebagai output
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Awalnya semua relay mati
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Baca status tombol dengan debouncing
  int buttonState = digitalRead(BUTTON_PIN);
  
  // Cek jika tombol berubah status
  if (buttonState != lastButtonState) {
    lastDebounceTime = currentMillis;
  }
  
  // Debouncing dan deteksi tekan tombol
  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW && !buttonPressed) {
      Serial.println("Tombol GPIO4 ditekan");
      buttonPressed = true;
    } else if (buttonState == HIGH) {
      buttonPressed = false;
    }
  }
  
  // Update status tombol terakhir
  lastButtonState = buttonState;
  
  // Kontrol relay berdasarkan interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Matikan semua relay
    for (int i = 0; i < numRelays; i++) {
      digitalWrite(relayPins[i], LOW);
    }
    
    // Aktifkan relay saat ini
    digitalWrite(relayPins[currentRelay], HIGH);
    
    // Pindah ke relay berikutnya
    currentRelay = (currentRelay + 1) % numRelays;
  }
}