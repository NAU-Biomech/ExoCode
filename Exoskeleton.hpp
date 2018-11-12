#ifndef EXOSKELETON_HEADER
#define EXOSKELETON_HEADER
#include "Leg.hpp"
#include "Pins.hpp"
#include <Metro.h>
#include "Report.hpp"

class Exoskeleton{
private:
  void fillLocalReport(ExoReport* report);
  void disableMotors();
  void enableMotors();

  bool resetting_motors = false;
  Metro motor_shutdown = Metro(16);
  Metro motor_startup = Metro(8);

// TODO Fully implement the fsr calibration
// ===== FSR Parameters =====
  int FSR_FIRST_Cycle = 1;
  int FSR_CAL_FLAG = 0;

// TODO Implement balance control
// ===== Receive_and_Transmit
  bool FLAG_BALANCE = false;
  bool FLAG_BALANCE_BASELINE = false;

  // TODO connect to auto kf methods
// ===== Auto KF =====
  int flag_auto_KF = 0;

  Leg* left_leg;
  Leg* right_leg;
  Metro BnoControl = Metro(10);

public:
  Exoskeleton(ExoPins* exoPins);
  void initialize();
  void measureSensors();
  bool checkMotorErrors();
  void takeFSRBaseline();
  void disableExo();
  void enableExo();
  void applyTorque();
  void applyStateMachine();
  void adjustControl();
  void resetStartingParameters();
  void setZeroIfSteadyState();
  void calibrateTorque();
  void calibrateFSRs();
  void setZeroIfStateState();
  void checkIMUs();
  void calibrateIMUs();
  void measureIMUs();
  ExoReport* generateReport();
  void fillReport(ExoReport* report);
};

#endif
