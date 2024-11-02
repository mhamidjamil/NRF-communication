#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

// Define the CE and CSN pins for nRF24L01
#define CE_PIN 4
#define CSN_PIN 5

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);
int buzzer = 33;
bool monitoring = true;

// Set the nRF24L01 address (same for sender and receiver)
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

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
  checkSerialCommands();
  if (radio.available()) {
    char text[32] = {0};             // Match buffer size to expected message
    radio.read(&text, sizeof(text)); // Read the message

    // Display the received message
    Serial.print("Received: ");
    Serial.println(text);

    // Additional action (e.g., toggling buzzer) based on received data
    if (isIn(text, "Movement Alert")) {
      movementAlert();
    }
  }
}

void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (isIn(command, "start monitoring")) {
      Serial.print("Monitoring started");
      monitoring = true;
    } else if (isIn(command, "stop monitoring")) {
      monitoring = false;
      Serial.print("Monitoring stoped");
    } else {
      println("Input not defined");
    }
  }
}

bool isIn(String mainString, String toFind) {
  return mainString.indexOf(toFind) != -1;
}

bool isIn(String mainString, String toFind_1, String toFind_2) {
  return (isIn(mainString, toFind_1) || isIn(mainString, toFind_2));
}

bool isIn(String mainString, String toFind_1, String toFind_2,
          String toFind_3) {
  return (isIn(mainString, toFind_1) || isIn(mainString, toFind_2) ||
          isIn(mainString, toFind_3));
}

void println(String str) { Serial.println(str); }
void print(String str) { Serial.print(str); }

void movementAlert() {
  if (!monitoring)
    return;
  beep();
  flash();
}

void beep() { beep(3, 1000); }

void beep(int howMany, int howLong) {
  for (int i = 0; i < howMany; i++) {
    digitalWrite(buzzer, HIGH);
    Delay(howLong / 2);
    digitalWrite(buzzer, LOW);
    Delay(howLong / 2);
  }
}

void flash() {}

void Delay(int delay_in_ms) {
  // custom delay to manage important processes
  for (int i = 0; i < delay_in_ms; i += 10)
    delay(10);
}