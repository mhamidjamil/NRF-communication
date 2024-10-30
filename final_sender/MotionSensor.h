#include <Wire.h>

class MotionSensor {
public:
  MotionSensor(int mpuAddr, int motionThreshold);
  void begin();
  bool isSignificantMovement();
  String getMotionData();

private:
  int16_t accelerometer_x, accelerometer_y, accelerometer_z;
  int mpuAddress;
  int threshold;
  int mainX = 0, mainY = 0;
  int calculateChange(int currentValue, int previousValue);
};
