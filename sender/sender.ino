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

  // Set the address for writing data
  radio.openWritingPipe(address);

  // Set the power level to minimum to reduce interference
  radio.setPALevel(RF24_PA_MIN);

  // Stop listening (since we're sending data)
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello from ESP32 Sender!";

  // Send the data
  bool result = radio.write(&text, sizeof(text));

  if (result) {
    Serial.println("Data Sent: Hello from ESP32 Sender!");
  } else {
    Serial.println("Error: Data not sent.");
  }

  delay(1000); // Send data every second
}
