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
  // Start the Serial Monitor
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  digitalWrite(led, HIGH);
  // Initialize the nRF24L01 module
  if (!radio.begin()) {
    Serial.println("nRF24L01 is not detected or failed to initialize.");
    while (1)
      ; // Stop the program if nRF24L01 fails to initialize
  }

  // Set the address for the reading pipe (receiving data)
  radio.openReadingPipe(0, address);

  // Set power level to minimum to reduce interference
  radio.setPALevel(RF24_PA_MIN);

  // Start listening for data
  radio.startListening();
}

void loop() {
  // Check if there's any data available from the sender
  if (radio.available()) {
    char text[32] = {0};             // Buffer to store received data
    radio.read(&text, sizeof(text)); // Read the data

    // Print the received data to the Serial Monitor
    Serial.print("Received: ");
    Serial.println(text);
  }
}
