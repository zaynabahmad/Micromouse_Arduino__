#include <SoftwareSerial.h>

SoftwareSerial HC05(17, 16); // Define SoftwareSerial object for HC-05 (TX, RX)

void setup() {
  Serial.begin(9600);  // Serial monitor for debugging
  HC05.begin(9600);    // Default baud rate for HC-05 module

  Serial.println("HC-05 Bluetooth Module Test");
  Serial.println("Enter '1' to turn on LED, '0' to turn it off.");
}

void loop() {
  if (HC05.available()) {
    char command = HC05.read();
    if (command == '1') {
      digitalWrite(44, HIGH); // Turn on LED on pin 13
      Serial.println("LED is ON");
    }
    else if (command == '0') {
      digitalWrite(44, LOW);  // Turn off LED on pin 13
      Serial.println("LED is OFF");
    }
  }

  if (Serial.available()) {
    char response = Serial.read();
    HC05.write(response); // Send data received from Serial Monitor to HC-05
  }
}
