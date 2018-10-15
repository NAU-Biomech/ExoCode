#ifndef MOTOR_HEADER
#define MOTOR_HEADER
#include <PID_v2.h>

#include "Parameters.h"
#include "Utils.h"

class Motor{
private:
  unsigned int torque_sensor_pin;
  unsigned int motor_pin;
  unsigned int motor_error_pin;

  double measureRawTorque();
  double measureRawCalibratedTorque();
public:
  Motor(int motor_pin, int torque_sensor_pin, int err_pin);
  double getTorque();
  void measureTorque();
  void measureError();
  bool hasErrored();
  bool applyTorque(int state);
  void autoKF(int state);
  void startTorqueCalibration();
  void updateTorqueCalibration();
  void endTorqueCalibration();
  void writeToMotor(int value);

  bool inErrorState;

  double sign = 1;

  double torque_measurements[TORQUE_AVERAGE_COUNT] = {0};

  double averaged_torque;

  double PID_Setpoint, Input, Output;
  PID pid = PID(&Input, &Output, &PID_Setpoint, PID_DEFAULTS[0], PID_DEFAULTS[1], PID_DEFAULTS[2], DIRECT);

  Average* pid_avg_err = new Average();
  Clamp* kf_clamp = new Clamp(MAX_KF, MIN_KF);

  double KF = 1;

  Average* torque_calibration_average = new Average();
  double torque_calibration_value = 0;

  int torque_address;

  double Setpoint, Setpoint_Pctrl;
  double Previous_Setpoint = 0;
  double Setpoint_earlyStance = 0.25 * Setpoint;
  double Dorsi_Setpoint;
  double Previous_Dorsi_Setpoint;

  double New_PID_Setpoint = 0.0;
  double Old_PID_Setpoint = 0.0;

  double zero_torque;
};

#endif
