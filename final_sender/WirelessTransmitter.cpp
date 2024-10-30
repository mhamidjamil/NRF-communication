#include "WirelessTransmitter.h"

WirelessTransmitter::WirelessTransmitter(int cePin, int csnPin,
                                         const byte *address)
    : radio(cePin, csnPin), pipeAddress(address) {}

void WirelessTransmitter::begin() {
  radio.begin();
  radio.openWritingPipe(pipeAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

bool WirelessTransmitter::sendAlert(const char *message) {
  return radio.write(&message, sizeof(message));
}
