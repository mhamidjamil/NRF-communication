#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

// Define the CE and CSN pins for nRF24L01
#define CE_PIN 4
#define CSN_PIN 5

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);
int led = 33;

// Set the nRF24L01 address (same for sender and receiver)
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  if (!radio.begin()) {
    Serial.println("nRF24L01 is not detected or failed to initialize.");
    while (1)
      ; // Stop if initialization fails
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = {0};             // Match buffer size to expected message
    radio.read(&text, sizeof(text)); // Read the message

    // Display the received message
    Serial.print("Received: ");
    Serial.println(text);

    // Additional action (e.g., toggling LED) based on received data
    if (strcmp(text, "Motion Detected!") == 0) {
      digitalWrite(led, LOW); // Example action for received signal
    }
  }
}
