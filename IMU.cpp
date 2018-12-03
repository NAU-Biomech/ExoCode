#include "Arduino.hpp"
#include "IMU.hpp"

IMU::IMU(ImuPort* imu_port, unsigned int address){

  bno = new Adafruit_BNO055(WIRE_BUS, 1, address, I2C_MASTER, imu_port->getPins(),
                            I2C_PULLUP_EXT, I2C_RATE_100, I2C_OP_MODE_ISR);

  for(int i = 0; i < 3;i++){
    bearings[i] = 0;
  }

  if (!bno->begin()) {
    Serial.println("No IMU detected");
  }
}

IMU::~IMU(){
  delete bno;
}

void IMU::calibrate(){
  sensors_event_t event;
  Serial.println("IMU setup... calibrating");
  while (!bno->isFullyCalibrated()) {
    bno->getEvent(&event);

    Serial.print("X: ");
    Serial.print(event.orientation.x);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y);
    Serial.print("\tZ: ");
    Serial.print(event.orientation.z);

    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno->getCalibration(&system, &gyro, &accel, &mag);
    /* Optional: Display calibration status */
    Serial.print("\tSys:");
    Serial.print(system);
    Serial.print(" G:");
    Serial.print(gyro);
    Serial.print(" A:");
    Serial.print(accel);
    Serial.print(" M:");
    Serial.print(mag);

    /* New line for the next sample */
    Serial.println("");

    /* Wait the specified delay before requesting new data */
    delay(BNO055_SAMPLERATE_DELAY_MS);
  }
}

void IMU::measure(){
  if (imu_measure_limiter.check()){
	  sensors_event_t event;
	  bno->getEvent(&event);
    this->bearings[0] = event.orientation.x;
    this->bearings[1] = event.orientation.y;
    this->bearings[2] = event.orientation.z;
    imu_measure_limiter.reset();
  }
}

void IMU::getOrientation(double* orientation){
  orientation[0] = this->bearings[0];
  orientation[1] = this->bearings[1];
  orientation[2] = this->bearings[2];
}

IMUReport* IMU::generateReport(){
  IMUReport* report = new IMUReport();
  fillLocalReport(report);
  return report;
}

void IMU::fillReport(IMUReport* report){
  fillLocalReport(report);
}

void IMU::fillLocalReport(IMUReport* report){
  getOrientation(report->orientation);
}
