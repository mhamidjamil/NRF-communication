#include "MotionSensor.h"

MotionSensor::MotionSensor(int mpuAddr, int motionThreshold)
    : mpuAddress(mpuAddr), threshold(motionThreshold) {}

void MotionSensor::begin() {
  Wire.begin();
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

bool MotionSensor::isSignificantMovement() {
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpuAddress, 6, true);

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();

  int avgChange = (calculateChange(accelerometer_x, mainX) +
                   calculateChange(accelerometer_y, mainY)) /
                  2;

  mainX = accelerometer_x;
  mainY = accelerometer_y;

  return avgChange > threshold;
}

String MotionSensor::getMotionData() {
  return String("X: ") + String(accelerometer_x) +
         " Y: " + String(accelerometer_y) + " Z: " + String(accelerometer_z);
}

int MotionSensor::calculateChange(int currentValue, int previousValue) {
  return abs(currentValue - previousValue);
}
