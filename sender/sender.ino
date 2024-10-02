#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

// CE and CSN pins configuration
#define CE_PIN 4   // GPIO4 -> D2
#define CSN_PIN 15 // GPIO15 -> D8

RF24 radio(CE_PIN, CSN_PIN); // Create RF24 object

// Unique address for communication
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  // Initialize the nRF24L01 radio
  radio.begin();

  // Set the address to transmit to
  radio.openWritingPipe(address);

  // Set the transmission to only acknowledge packets
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  const char text[] = "Hello, world!";

  // Send the text
  radio.write(&text, sizeof(text));

  Serial.println("Data Sent: Hello, world!");

  delay(1000); // Send every second
}
