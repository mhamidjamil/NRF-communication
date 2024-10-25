#include <MPU6050.h> // Include the MPU6050 library
#include <Wire.h>

MPU6050 mpu; // Create an MPU6050 object

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Initialize the MPU6050
  Wire.begin(); // Initialize I2C communication
  mpu.begin();  // Initialize the MPU6050 sensor

  // Check if the MPU6050 is successfully connected
  if (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    while (1)
      ; // Stop the program if MPU6050 is not connected
  }

  // Configure the sensor
  mpu.calcOffsets(); // Calibrate the MPU6050 to get accurate data

  Serial.println("MPU6050 initialized successfully!");
}

void loop() {
  // Read accelerometer and gyroscope data
  mpu.update(); // Update sensor readings

  // Print accelerometer values
  Serial.print("AccelX: ");
  Serial.print(mpu.getAccX());
  Serial.print(" | AccelY: ");
  Serial.print(mpu.getAccY());
  Serial.print(" | AccelZ: ");
  Serial.println(mpu.getAccZ());

  // Print gyroscope values
  Serial.print("GyroX: ");
  Serial.print(mpu.getGyroX());
  Serial.print(" | GyroY: ");
  Serial.print(mpu.getGyroY());
  Serial.print(" | GyroZ: ");
  Serial.println(mpu.getGyroZ());

  delay(500); // Delay to slow down the output
}
