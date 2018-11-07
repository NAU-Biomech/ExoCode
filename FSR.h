#ifndef FSR_HEADER
#define FSR_HEADER

class FSR{
private:
  bool isCalibrating = false;
  unsigned long fsrCalibrationStartTime;
  void startCalibration();
  void updateCalibration();
  void endCalibration();

public:
  FSR(int pin);
  double calibrate();
  void measureForce();
  double getForce();
  double getBalanceReference();

  unsigned int pin;

  double force = 0;
  double peak_force = 0;

  double fsr = 0;
  int address_FSR;
  int baseline_address;
  double baseline_value;
};

class FSRGroup{
private:
  int fsr_count;
  double calibration_peak;
  double fsr_percent_thresh = 0.9;
  FSR** fsrs;
  Max* max_fsr_voltage = Max();
  Max* max_fsr_percentage = Max();
  double plant_peak_mean = 0;
  RunningAverage* plant_peak_averager = RunningAverage();

  void startCalibration();
  void updateCalibration();

public:
  FSRGroup(FSRPins* fsr_pins, int fsr_count);

  void measureForce();
  double getForce();
  void calibrate();
  double getBalanceReference();
  double getThreshold();
  void setPercentageThreshold(double percent);
  void FSRGroup::resetMaxes();
  void FSRGroup::updateMaxes();
  void FSRGroup::getPercentage();
  void FSRGroup::getMaxPercentage();
  void FSRGroup::startBaseline();
  void FSRGroup::updateBaseline();
  double force;
};
#endif
