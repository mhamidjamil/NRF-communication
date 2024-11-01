#include "MotionSensor.h"
#include <Arduino.h>

MotionSensor::MotionSensor(int mpuAddr, int motionThreshold)
    : mpuAddress(mpuAddr), threshold(motionThreshold) {}

void MotionSensor::begin() {
  Wire.begin();
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void MotionSensor::printMotionData(int x_axis, int y_axis, int z_axis,
                                   int avgChange) {
  Serial.println("X: " + String((x_axis)) + " Y: " + String(y_axis) +
                 " Z: " + String(z_axis) + " avgChange: " + String(avgChange));
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

  printMotionData(accelerometer_x, accelerometer_y, accelerometer_z, avgChange);

  bool significantMovement = avgChange > threshold;
  if (significantMovement) {
    Serial.println("\n-------------------------------------------------\n");
    mainX = accelerometer_x;
    mainY = accelerometer_y;
    delay(200);
  }

  return significantMovement;
}

int MotionSensor::calculateChange(int currentValue, int previousValue) {
  return abs(currentValue - previousValue);
}

void MotionSensor::setThreshold(int currentValue) {
  this->threshold = currentValue;
}

int MotionSensor::getThreshold() { return this->threshold; }