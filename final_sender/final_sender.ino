#include "MotionSensor.h"
#include "WirelessTransmitter.h"
#include <Arduino.h>

// Motion sensor and wireless transmitter setup
const int MPU_ADDR = 0x68;
const byte address[6] = "00001";

MotionSensor motionSensor(MPU_ADDR, 200);
WirelessTransmitter transmitter(4, 5, address);

void setup() {
  Serial.begin(115200);
  motionSensor.begin();
  transmitter.begin();
  Serial.println("System Initialized.");

  // Create tasks
  xTaskCreate(checkMovementTask, "MotionCheck", 1000, NULL, 1, NULL);
}

void loop() {
  // Main loop remains empty as tasks handle the functionality
}

void checkMovementTask(void *pvParameters) {
  while (true) {
    if (motionSensor.isSignificantMovement()) {
      Serial.println("Motion detected!");
      if (transmitter.sendAlert("Movement Alert")) {
        Serial.println("Alert sent via nRF24L01!");
      } else {
        Serial.println("Failed to send alert.");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(500)); // Task delay for efficiency
  }
}
