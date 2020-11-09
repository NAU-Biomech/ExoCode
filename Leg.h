#ifndef LEG_HEADER
#define LEG_HEADER
const int dim_FSR = 30;
const int dim = 5;

#include "PID_v2.h"
#include "Control_Adjustment.h"

struct Leg {
  int torque_sensor_ankle_pin;
  int torque_sensor_knee_pin;  // TN 5/9/19
  int motor_ankle_pin, motor_knee_pin;
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

  double Tarray_Knee[dim] = {0};   // TN 5/9/19
  double* TarrayPoint_Knee = &Tarray_Knee[0];   // TN 5/9/19
  double Average_K = 0;   // SS  9/18/2019

  double sign = 1;

  // In A_Exo post_includes
  unsigned int pin_err, pin_err_Knee;

  double store_KF = 0;

  double previous_curr_voltage;
  double previous_torque_average;

  double Heel_Moment_Arm;
  double Toe_Moment_Arm = 5;

  volatile double Average_Volt;
  volatile double Average_Volt_Heel;
  volatile double Average_Trq;
  volatile double Average_Trq_Knee;  // SS  9/18/2019
  volatile double FSR_Combined_Average;
  volatile double FSR_Toe_Average;
  volatile double FSR_Heel_Average;
  volatile bool motor_error = false;
  volatile int Time_error_counter;

  //  SS  10/18/2020
  volatile double Angle_Thigh;
  volatile double Angle_Shank;
  volatile double Angle_Foot;

  volatile double PrevAngle_Thigh[9];
  volatile double PrevAngle_Shank[9];
  volatile double PrevAngle_Foot[9];

  volatile double AngleAve_Thigh;
  volatile double AngleAve_Shank;
  volatile double AngleAve_Foot;

  volatile double AngularVel_Thigh;
  volatile double AngularVelAve_Thigh;
  volatile double PrevAngularVelAve_Thigh;
  volatile double AngularVel_Shank;
  volatile double AngularVelAve_Shank;
  volatile double PrevAngularVelAve_Shank;
  volatile double AngularVel_Foot;
  volatile double AngularVelAve_Foot;
  volatile double PrevAngularVelAve_Foot;

  volatile double AngularVel_Thigh_Filt;
  volatile double AngularVel_Shank_Filt;
  volatile double AngularVel_Foot_Filt;

  volatile double PrevAngularVel_Thigh[24];
  volatile double PrevAngularVel_Shank[24];
  volatile double PrevAngularVel_Foot[24];
  

  volatile double PrevAngularAcc_Thigh[24];
  volatile double PrevAngularAcc_Shank[24];
  volatile double PrevAngularAcc_Foot[24];
  
  volatile double AngularAcc_Thigh;
  volatile double AngularAccAve_Thigh;
  volatile double AngularAcc_Shank;
  volatile double AngularAccAve_Shank;
  volatile double AngularAcc_Foot;
  volatile double AngularAccAve_Foot;

  double AnkleMoment;
  double AnkleMoment_Mod;
  double KneeMoment;
  double KneeMoment_Mod;
  double HipMoment;
  double HipMoment_Mod;

  volatile double FSR_Toe_Balance_Baseline;
  volatile double FSR_Heel_Balance_Baseline;
  volatile double FSR_Toe_Steady_Balance_Baseline;
  volatile double FSR_Heel_Steady_Balance_Baseline;

  volatile double COP_Toe_ratio, COP_Heel_ratio, COP_Foot_ratio;

  double Dynamic_multiplier, Steady_multiplier;

  // Auto_KF.h
  double ERR, ERR_Knee;
  double Max_Measured_Torque;
  double max_KF = 3;
  double min_KF = 0.9;
  double MaxPropSetpoint;
  bool auto_KF_update = false;

  // TN 5/9/19
  double Max_Measured_Torque_Knee;
  double max_KF_Knee = 1.5;
  double min_KF_Knee = 0.9;
  double MaxPropSetpoint_Knee;
  bool auto_KF_Knee_update = false;

  // Calibrate_and_Read_Sensors.h
  double FSR_Ratio;
  double FSR_Ratio_Toe;  // SS  9/18/2019
  double FSR_Ratio_Heel;
  double FSR_Ratio_HeelMinusToe;  // SS 9/10/2019
  double FSR_Ratio_Ankle;  // SS 2/5/2020
  double FSR_Ratio_Knee;  // SS 2/5/2020
  double INTEG_Ratio_Toe;           // SS 3/29/2020
  double INTEG_Ratio_Heel;          // SS 3/29/2020
  double INTEG_Ratio_HeelMinusToe;  // SS 3/29/2020
  double INTEG_Ratio_Ankle;         // SS 3/29/2020
  double Moment_Ratio_Ankle;         // SS 10/18/2020

  
  double INTEG_Ratio_Knee;          // SS 3/29/2020
  double Max_FSR_Ratio;
  double Max_FSR_Ratio_Toe;
  double Max_FSR_Ratio_Heel;
  double Max_FSR_Ratio_HeelMinusToe;  // SS 9/10/2019
  double Max_FSR_Ratio_Ankle;  // SS 2/5/2020
  double Max_FSR_Ratio_Knee;  // SS 2/5/2020
  double Max_INTEG_Ratio_Toe;           // SS 3/29/2020
  double Max_INTEG_Ratio_Heel;          // SS 3/29/2020
  double Max_INTEG_Ratio_HeelMinusToe;  // SS 3/29/2020
  double Max_INTEG_Ratio_Ankle;         // SS 3/29/2020
  double Max_INTEG_Ratio_Knee;          // SS 3/29/2020
  double Angular_Impulse;// SS 6/8/2020
  double Angular_Impulse_Knee;// SS 6/8/2020

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

  double cal_counter; //  SS  11/8/2020
  double fsr_Toe_offset = 0; //  SS  11/8/20202020
  double fsr_Heel_offset = 0; //  SS  11/8/2020
  
  double FSR_Toe_Abs; //  SS  11/8/2020
  double FSR_Heel_Abs; //  SS  11/8/2020
  
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
  double baseline_value, baseline_value_Toe;

  //int baseline_address_Heel;   // SS  9/18/2019
  double baseline_value_Heel;   // SS  9/18/2019
  double baseline_value_HeelMinusToe;  // SS 9/10/2019
  double baseline_value_Knee; // SS 2/5/2020
  double baseline_value_Ankle; // SS 2/5/2020

  double baseline_Integ_Toe;          //  SS  3/29/2020
  double baseline_Integ_Heel;         //  SS  3/29/2020
  double baseline_Integ_HeelMinusToe; //  SS  3/29/2020
  double baseline_Integ_Ankle;        //  SS  3/29/2020
  double baseline_Integ_Knee;         //  SS  3/29/2020

  // PID_and_Ctrl_Parameters.h
  double torque_calibration_value_Ankle = 0;
  double torque_calibration_value_Knee = 0;  // SS  9/18/2019
  double T_act;
  int Vol, Vol_Knee;

#ifdef ENABLE_PWM   //PID Gains are different for PWM control
  double kp = 600;
  double ki = 0;
  double kd = 3;
  //PWM Gains for Knee control:  // SS  9/18/2019
  double kp_Knee = 600;
  double ki_Knee = 0;
  double kd_Knee = 3;
#else
  double kp = 700;
  double ki = 0;
  double kd = 3;
  //PID Gains for Knee control:  // SS  9/18/2019
  double kp_Knee = 700;
  double ki_Knee = 0;
  double kd_Knee = 3;
#endif
  double KF = 1;
  double KF_Knee = 1;  // SS  9/18/2019

  double PID_Setpoint, Input, Output;
  PID pid = PID(&Input, &Output, &PID_Setpoint, kp, ki, kd, DIRECT);

  double PID_Setpoint_Knee, Input_Knee, Output_Knee;  // SS  9/18/2019
  PID pid_Knee = PID(&Input_Knee, &Output_Knee, &PID_Setpoint_Knee, kp_Knee, ki_Knee, kd_Knee, DIRECT);  // SS  9/18/2019

  double Setpoint_Ankle, Setpoint_Ankle_Pctrl;
  double Previous_Setpoint_Ankle = 0;
  double Previous_Setpoint_Ankle_Pctrl = 0;
  double* p_Setpoint_Ankle = &Setpoint_Ankle;
  double* p_Setpoint_Ankle_Pctrl = &Setpoint_Ankle_Pctrl;
  double Setpoint_Knee, Setpoint_Knee_Pctrl;  // SS  9/18/2019
  double Previous_Setpoint_Knee = 0;
  double Previous_Setpoint_Knee_Pctrl = 0;  // SS  9/18/2019
  double* p_Setpoint_Knee = &Setpoint_Knee;
  double* p_Setpoint_Knee_Pctrl = &Setpoint_Knee_Pctrl;

  double Setpoint_earlyStance = 0.25 * Setpoint_Ankle;
  double Dorsi_Setpoint_Ankle;
  double Previous_Dorsi_Setpoint_Ankle;
  double* p_Dorsi_Setpoint_Ankle = &Dorsi_Setpoint_Ankle;
  double* p_Previous_Dorsi_Setpoint_Ankle = &Previous_Dorsi_Setpoint_Ankle;

  // TN 5/8/19
  double Setpoint_earlyStance_Knee = 0.25 * Setpoint_Knee;
  double Flexion_Setpoint_Knee;
  double Previous_Flexion_Setpoint_Knee;
  double* p_Flexion_Setpoint_Knee = &Flexion_Setpoint_Knee;
  double* p_Previous_Flexion_Setpoint_Knee = &Previous_Flexion_Setpoint_Knee;


  // Proportional_Ctrl.h
  double Prop_Gain = 1;
  double Prop_Gain_Knee = 1;  // SS  9/18/2019

  // Reference_ADJ.h
  double stateTimerCount;
  double flag_1 = 0;
  double time_old_state;

  double activate_in_3_steps_Ankle = 0;
  double first_step_Ankle = 1;
  double coef_in_3_steps_Ankle = 0;
  double start_step_Ankle = 0;
  double num_3_steps_Ankle = 0;
  double store_3sec_N1 = N1; // Not sure if this one is needed

  double activate_in_3_steps_Knee = 0;
  double first_step_Knee = 1;
  double coef_in_3_steps_Knee = 0;
  double start_step_Knee = 0;
  double num_3_steps_Knee = 0;

  double coef_in_3_steps_Pctrl = 0;
  double store_N1 = 0;
  double set_2_zero = 0;
  double One_time_set_2_zero = 1;

  // Shaping_Parameters.h
  double exp_mult = 1500.0;
  double exp_mult_Knee = 1500.0;
  boolean sigm_done, sigm_done_Knee;  // SS  9/18/2019

  double New_PID_Setpoint = 0.0;
  double Old_PID_Setpoint = 0.0;

  double New_PID_Setpoint_Knee = 0.0;   // SS  9/18/2019
  double Old_PID_Setpoint_Knee = 0.0;  // SS  9/18/2019

  double N3 = 200;
  double N2 = 200;
  double N1 = 4;

  double old_N3 = 200;
  double old_N2 = 200;
  double old_N1 = 4;

  long sig_time = 0;
  long sig_time_old = 0;
  long sig_time_Knee = 0;
  long sig_time_old_Knee = 0;

  int n_iter, N_step;
  int n_iter_Knee, N_step_Knee;


  // State_Machine_Parameters.h

  int state = 1;
  int old_state = 11;
  int state_old = 11;
  int state_count_13 = 0;
  int state_count_31 = 0;
  int state_count_12 = 0;
  int state_count_21 = 0;
  int state_count_23 = 0;
  int state_count_32 = 0;

  double state_3_start_time = 0;
  double state_2_start_time = 0;
  double state_1_start_time = 0;
  double start_from_1 = 0;
  double start_from_3 = 0;
  double start_time_Ankle = 0;  // SS  9/18/2019
  double start_time_Knee = 0;  // SS  9/18/2019
  double state_3_stop_time = 0;
  double state_3_duration = 0;
  double state_2_stop_time = 0;
  double state_2_duration = 0;

  double Heel_Pos = -0.07;
  double Toe_Pos = 0.20;
  double COP = 0;

  //BIOFEEDBACK
  bool BioFeedback_Baseline_flag = false;
  double Heel_Strike;
  int Heel_Strike_Count, Heel_Strike_baseline;
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
  //char AorK = ' ';  // TN 5/9/19

  double zero;
  double torque_error_counter;
  double stridetime_update, stridelength_update;
  double stridetime_baseline, stridelength_baseline, stridelength_target;
  double HS1, HS2, HS4;
  double stridetime_target;
  double stridetime;
  double score;


  //Optimization-----------------------------------
  double T_Opt_p, Setpoint_Ankle_Opt, Setpoint_Knee_Opt;  // SS  9/18/2019
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
