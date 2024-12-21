#include <Arduino.h>

// Pin relay
#define RLY1 16
#define RLY2 14
#define RLY3 12
#define RLY4 13

// Konstanta
const unsigned long onOffInterval = 500; // Durasi ON/OFF dalam ms
const int toggleCount = 4;               // Jumlah ON/OFF per relay

// Variabel global
unsigned long previousMillis = 0;
int currentRelay = 0;                    // Relay yang sedang aktif
int currentToggle = 0;                   // Jumlah ON/OFF yang sudah dilakukan

// Array pin relay
int relayPins[] = {RLY1, RLY2, RLY3, RLY4};
const int numRelays = sizeof(relayPins) / sizeof(relayPins[0]);

void setup() {
  // Konfigurasi pin sebagai output
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Awalnya semua relay mati
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // Periksa apakah sudah waktunya untuk toggle
  if (currentMillis - previousMillis >= onOffInterval) {
    previousMillis = currentMillis;

    // Toggle relay saat ini
    digitalWrite(relayPins[currentRelay], !digitalRead(relayPins[currentRelay]));
    currentToggle++;

    // Jika relay saat ini sudah toggle 4 kali, pindah ke relay berikutnya
    if (currentToggle >= toggleCount * 2) { // ON + OFF = 2 toggle per siklus
      digitalWrite(relayPins[currentRelay], LOW); // Pastikan relay mati
      currentToggle = 0;                          // Reset toggle counter
      currentRelay = (currentRelay + 1) % numRelays; // Pindah ke relay berikutnya
    }
  }
}
