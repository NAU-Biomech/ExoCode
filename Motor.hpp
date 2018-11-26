#ifndef MOTOR_HEADER
#define MOTOR_HEADER
#include "Parameters.hpp"
#include "Utils.hpp"
#include "Shaping_Functions.hpp"
#include "Control_Algorithms.hpp"
#include "Ports.hpp"
#include "Report.hpp"
#include <PID_v2.h>

class Motor{
private:
  void fillLocalReport(MotorReport* report);

  double output_sign;
  OutputPort* motor_port;
  InputPort* motor_error_port;

  bool in_error_state;
  double zero_offset;

public:
  Motor(InputPort* motor_error_port, OutputPort* motor_port, int output_sign);
  void measureError();
  bool hasErrored();
  void write(double value);
  void setSign(int sign);
  MotorReport* generateReport();
  void fillReport(MotorReport* report);
};

#endif
