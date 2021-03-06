#ifndef LEG_HEADER
#define LEG_HEADER
const int dim_FSR = 30;
const int dim = 5;

#include "PID_v2.h"
#include "Control_Adjustment.h"

struct Leg {
  int torque_sensor_ankle_pin;
  int motor_ankle_pin;
  // In A_Exo pre-includes
  double FSR_Average_array[dim_FSR] = {0};
  double* p_FSR_Array = &FSR_Average_array[0];
  double Curr_FSR_Toe = 0;

  double FSR_Average_array_Heel[dim_FSR] = {0};
  double* p_FSR_Array_Heel = &FSR_Average_array_Heel[0];
  double Curr_FSR_Heel = 0;

  double Tarray[dim] = {0};
  double* TarrayPoint = &Tarray[0];
  double Average = 0;

  double sign = 1;

  // In A_Exo post_includes
  unsigned int pin_err;

  double store_KF = 0;

  double previous_curr_voltage;
  double previous_torque_average;

  volatile double Average_Volt;
  volatile double Average_Volt_Heel;
  volatile double Average_Trq;
  volatile double FSR_Combined_Average;
  volatile double FSR_Toe_Average;
  volatile double FSR_Heel_Average;
  volatile bool motor_error = false;
  volatile int Time_error_counter;

  volatile double FSR_Toe_Balance_Baseline;
  volatile double FSR_Heel_Balance_Baseline;
  volatile double FSR_Toe_Steady_Balance_Baseline;
  volatile double FSR_Heel_Steady_Balance_Baseline;

  volatile double COP_Toe_ratio, COP_Heel_ratio, COP_Foot_ratio;

  double Dynamic_multiplier, Steady_multiplier;

  // Auto_KF.h
  double Torque_Sum_90P;
  double Mean_Torque_90P;
  double ERR;
  double Max_Measured_Torque;
  double max_KF = 1.5;
  double min_KF = 0.9;
  int count_err;
  double Mean_Measured_Torque;
  bool auto_KF_update = true;

  // Calibrate_and_Read_Sensors.h
  double FSR_Ratio;
  double Max_FSR_Ratio;

  // Combined_FSR.h
  double fsr_Combined_peak_ref;
  double Curr_Combined;

  // FSR_Parameters.h
  unsigned int fsr_sense_Heel;
  unsigned int fsr_sense_Toe;

  double fsr_Heel = 0;
  double fsr_Toe = 0;
  double fsr_Heel_peak_ref = 0;
  double fsr_Toe_peak_ref = 0;

  double fsr_percent_thresh_Heel = 0.1;
  double fsr_percent_thresh_Toe = 0.1;

  int FSR_baseline_FLAG = 0;
  int* p_FSR_baseline_FLAG = &FSR_baseline_FLAG;

  double Curr_Toe;
  double Curr_Heel;

  // Memory_Address.h
  int torque_address;
  int address_FSR;
  int baseline_address;
  double baseline_value;

  // PID_and_Ctrl_Parameters.h
  double torque_calibration_value = 0;
  double T_act;
  int Vol;

#ifdef ENABLE_PWM   //PID Gains are different for PWM control
  double kp = 600;
  double ki = 0;
  double kd = 3;
#else
  double kp = 700;
  double ki = 0;
  double kd = 3;
#endif
  double KF = 1;

  double PID_Setpoint, Input, Output;
  PID pid = PID(&Input, &Output, &PID_Setpoint, kp, ki, kd, DIRECT);

  double Setpoint_Ankle, Setpoint_Ankle_Pctrl;
  double Previous_Setpoint_Ankle = 0;
  double* p_Setpoint_Ankle = &Setpoint_Ankle;
  double* p_Setpoint_Ankle_Pctrl = &Setpoint_Ankle_Pctrl;
  double Setpoint_earlyStance = 0.25 * Setpoint_Ankle;
  double Dorsi_Setpoint_Ankle;
  double Previous_Dorsi_Setpoint_Ankle;
  double* p_Dorsi_Setpoint_Ankle = &Dorsi_Setpoint_Ankle;
  double* p_Previous_Dorsi_Setpoint_Ankle = &Previous_Dorsi_Setpoint_Ankle;


  // Proportional_Ctrl.h
  double Prop_Gain = 1;

  // Reference_ADJ.h
  double stateTimerCount;
  double flag_1 = 0;
  double time_old_state;

  double activate_in_3_steps = 0;
  double first_step = 1;
  double coef_in_3_steps = 0;
  double start_step = 0;
  double num_3_steps = 0;
  double store_3sec_N1 = N1; // Not sure if this one is needed

  double coef_in_3_steps_Pctrl = 0;
  double store_N1 = 0;
  double set_2_zero = 0;
  double One_time_set_2_zero = 1;

  // Shaping_Parameters.h
  double exp_mult = 1500.0;
  boolean sigm_flag = true;
  boolean sigm_done;

  double New_PID_Setpoint = 0.0;
  double Old_PID_Setpoint = 0.0;

  double N3 = 500;
  double N2 = 4;
  double N1 = 4;

  double old_N3 = 500;
  double old_N2 = 4;
  double old_N1 = 4;

  long sig_time = 0;
  long sig_time_old = 0;

  int n_iter, N_step;

  boolean signm_done = true;

  // State_Machine_Parameters.h
  int state = 1;
  int state_old = 1;
  int state_count_13 = 0;
  int state_count_31 = 0;
  int state_count_12 = 0;
  int state_count_21 = 0;
  int state_count_23 = 0;
  int state_count_32 = 0;

  double state_3_start_time = 0;
  double state_1_start_time = 0;
  double start_from_1 = 0;
  double start_from_3 = 0;
  double start_time = 0;

  double Heel_Pos = -0.07;
  double Toe_Pos = 0.20;
  double COP = 0;

  //BIOFEEDBACK
  bool BioFeedback_Baseline_flag = false;
  double Heel_Strike;
  double Heel_Strike_Count, Heel_Strike_baseline;
  double Heel_Strike_mean;
  double n_step_biofeedback = 1;
  double n_step_biofeedback_base = 4;
  unsigned int Potentiometer_pin;
  double Biofeedback_bias;
  double BioFeedback_desired;
  double Frequency;
  double Err_max;
  double min_knee_error = 5;
  double Biofeedback_ctrl_max;
  double Biofeedback_Volume = 0;

  bool BIO_BASELINE_FLAG = false;
  bool NO_Biofeedback = true;
  double start_time_Biofeedback;

  char whos = ' ';

  double zero;
  double torque_error_counter;

  //Optimization-----------------------------------
  double T_Opt_p, Setpoint_Ankle_Opt;
  double Previous_T_Opt = 0.1;
  double T_Opt = 0.1;
  double T_Opt_Setpoint = 0.1;

  double p0, dp0, ddp0, pf, dpf, ddpf, c0, c1, c2, c3, c4, c5;

  bool FLAG_UPDATE_VALUES = false;
  //------------------------------------------------

  // Torque_Speed_ADJ.h
  //steps steps;
  steps* p_steps;

};

Leg left_leg_value = Leg();
Leg right_leg_value = Leg();
Leg* left_leg = &left_leg_value;
Leg* right_leg = &right_leg_value;

void initialize_leg(Leg* leg);
void initialize_left_leg(Leg* left_leg);
void initialize_right_leg(Leg* right_leg);


#endif
