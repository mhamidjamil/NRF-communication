#include <MPU9250_asukiaaa.h>

// Create sensor instance
MPU9250_asukiaaa mySensor;

// Variables for accelerometer
float aX, aY, aZ, aSqrt;

// Variables for gyroscope
float gX, gY, gZ;

// Variables for magnetometer
float mX, mY, mZ, mDirection;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize I2C communication
  Wire.begin();

  // Link the I2C interface to the sensor
  mySensor.setWire(&Wire);

  // Initialize accelerometer, gyroscope, and magnetometer
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  Serial.println("MPU-9265 Sensor Initialized");
  Serial.println("--------------------------------------------");
}

void loop() {
  // Update accelerometer values
  mySensor.accelUpdate();
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  aSqrt = mySensor.accelSqrt(); // Combined acceleration

  // Update gyroscope values
  mySensor.gyroUpdate();
  gX = mySensor.gyroX();
  gY = mySensor.gyroY();
  gZ = mySensor.gyroZ();

  // Update magnetometer values
  mySensor.magUpdate();
  mX = mySensor.magX();
  mY = mySensor.magY();
  mZ = mySensor.magZ();
  mDirection = mySensor.magHorizDirection(); // Magnetic heading

  // Display data
  Serial.println("Accelerometer (m/s^2):");
  Serial.print("  X: ");
  Serial.print(aX);
  Serial.print(" | Y: ");
  Serial.print(aY);
  Serial.print(" | Z: ");
  Serial.print(aZ);
  Serial.print(" | Total: ");
  Serial.println(aSqrt);

  Serial.println("Gyroscope (°/s):");
  Serial.print("  X: ");
  Serial.print(gX);
  Serial.print(" | Y: ");
  Serial.print(gY);
  Serial.print(" | Z: ");
  Serial.println(gZ);

  Serial.println("Magnetometer (µT):");
  Serial.print("  X: ");
  Serial.print(mX);
  Serial.print(" | Y: ");
  Serial.print(mY);
  Serial.print(" | Z: ");
  Serial.print(mZ);
  Serial.print(" | Direction: ");
  Serial.println(mDirection);

  Serial.println("--------------------------------------------");

  // Add a small delay before the next update
  delay(500);
}
