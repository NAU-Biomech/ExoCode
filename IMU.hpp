#ifndef IMU_HEADER
#define IMU_HEADER
#include "Arduino.hpp"
#include "Parameters.hpp"
#include "Report.hpp"
#include "Port.hpp"

class IMU{
private:
  Adafruit_BNO055* bno;
  double bearings[3] = {0};
  Metro imu_measure_limiter = Metro(BNO055_SAMPLERATE_DELAY_MS);

public:
  IMU(ImuPort* imu_port, unsigned int address);
  ~IMU();
  void calibrate();
  void measure();
  void getOrientation(double* orientation);
  IMUReport* generateReport();
  void fillReport(IMUReport* report);
  void fillLocalReport(IMUReport* report);
};

#endif
