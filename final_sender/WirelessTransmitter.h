#include <RF24.h>

class WirelessTransmitter {
public:
  WirelessTransmitter(int cePin, int csnPin, const byte *address);
  void begin();
  bool sendAlert(const char *message);

private:
  RF24 radio;
  const byte *pipeAddress;
};
