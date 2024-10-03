#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>


// Define the CE and CSN pins for nRF24L01
#define CE_PIN 22
#define CSN_PIN 21

RF24 radio(CE_PIN, CSN_PIN); // Create a RF24 object

// Unique address for communication
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  // Initialize nRF24L01 radio
  if (!radio.begin()) {
    Serial.println("nRF24L01 is not connected or failed to initialize.");
    while (1)
      ; // Halt the program if initialization fails
  }

  // Set the address for reading data
  radio.openReadingPipe(0, address);

  // Set the power level to minimum
  radio.setPALevel(RF24_PA_MIN);

  // Start listening for data
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = {0}; // Buffer to store received data
    radio.read(&text, sizeof(text));

    Serial.print("Received: ");
    Serial.println(text);
  }
}
