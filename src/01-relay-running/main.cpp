#include <Arduino.h>

void setup() {
    // Start the serial communication
    Serial.begin(115200);
    // Wait for the serial port to connect (for debugging purposes)
    while (!Serial) {
        ;
    }
    // Print "Hello, World!" to the serial monitor
    Serial.println("Hello, World!");
}

void loop() {
    // Put your main code here, to run repeatedly
}
