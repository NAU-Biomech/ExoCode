#include <Arduino.h>
#include "IMU.hpp"
#include "System.hpp"

void setupIMU(Adafruit_BNO055* bno){
  if (IMU_ENABLED){
    if (!bno->begin())
    {
      Serial.println("No IMU detected haulting...");
    }
  }
}

void calibrateIMU(Adafruit_BNO055* bno){
  sensors_event_t event;
  Serial.println("IMU setup... calibrating");
  while (!bno->isFullyCalibrated()) {
    bno->getEvent(&event);

    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.print(event.orientation.z, 4);

    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno->getCalibration(&system, &gyro, &accel, &mag);
    /* Optional: Display calibration status */
    Serial.print("\tSys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.print(mag, DEC);

    /* New line for the next sample */
    Serial.println("");

    /* Wait the specified delay before requesting new data */
    delay(BNO055_SAMPLERATE_DELAY_MS);
  }
}

void updateIMU(Adafruit_BNO055* bno){
  if (IMU_ENABLED){
    euler = bno->getVector(Adafruit_BNO055::VECTOR_EULER);
  }
}
