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

void loop() { checkSerialCommands(); }

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
    vTaskDelay(pdMS_TO_TICKS(200)); // Task delay for efficiency
  }
}

void checkSerialCommands() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command.startsWith("set threshold")) {
      int new_threshold = command.substring(13).toInt();
      if (new_threshold > 0) {
        Serial.print("Threshold setting to ");
        Serial.println(new_threshold);
        motionSensor.setThreshold(new_threshold);
      } else {
        Serial.println("Invalid threshold value.");
      }
    } else if (isIn(command, "print values")) {
      println("Value of threshold is: " + String(motionSensor.getThreshold()));
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