#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

// Define the CE and CSN pins for nRF24L01
#define CE_PIN 4 
#define CSN_PIN 5

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Set the nRF24L01 address (same for sender and receiver)
const byte address[6] = "00001";

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Initialize the nRF24L01 module
  if (!radio.begin()) {
    Serial.println("nRF24L01 is not detected or failed to initialize.");
    while (1)
      ; // Stop the program if nRF24L01 fails to initialize
  }

  // Set the address for the writing pipe (sending data)
  radio.openWritingPipe(address);

  // Set power level to minimum to reduce interference
  radio.setPALevel(RF24_PA_MIN);

  // Stop listening (sender mode)
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello from ESP32 Sender!";

  // Send the data to the receiver
  bool result = radio.write(&text, sizeof(text));

  // Check if data was sent successfully
  if (result) {
    Serial.println("Data Sent: Hello from ESP32 Sender!");
  } else {
    Serial.println("Error: Data not sent.");
  }

  delay(1000); // Send data every second
}
