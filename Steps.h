#ifndef STEPS_HEADER
#define STEPS_HEADER
#include "Parameters.h"

class Steps{
public:
  int    n_steps;
  double dorsi_time;
  double plant_time;

  FixedAverage* plant_time_averager = new FixedAverage(n_step_baseline);
  FixedAverage* peak_time_averager = new FixedAverage(n_step_baseline);
  FixedAverage* dorsi_time_averager = new FixedAverage(n_step_baseline);
  Clamp* setpoint_clamp = new Clamp(Min_Prop, Max_Prop);
  bool flag_take_average = false;
  bool flag_N3_adjustment_time = false;
  double dorsi_mean;
  double plant_mean;
  double plant_peak_mean;
  int count_plant;
  int count_plant_base;
  bool flag_start_plant = false;
  bool flag_take_baseline = false;
  bool torque_adj = false;
  double Setpoint;
  double plant_mean_base;
  double voltage_peak_ref;
  double curr_voltage;
  double perc_l = 0.5;
  double fsr_percent_thresh_Toe = 0.9;
  double peak;
};

#endif