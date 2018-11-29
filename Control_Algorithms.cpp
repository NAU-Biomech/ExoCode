#include <Arduino.h>
#include "Control_Algorithms.hpp"
#include "Parameters.hpp"

ControlAlgorithm::ControlAlgorithm(StateType state){
  this->setpoint_clamp = new Clamp(Min_Prop, Max_Prop);
  activation_clamp = new Clamp(0,1);
}

double ControlAlgorithm::clamp_setpoint(double raw_setpoint){
  if(raw_setpoint == 0){
    return 0;
  }

  double setpoint_sign = fabs(raw_setpoint) / raw_setpoint;
  double setpoint = setpoint_sign * setpoint_clamp->clamp(fabs(raw_setpoint));
  return setpoint;
}

StateID ControlAlgorithm::getStateID(){
  return state_id;
}

void ControlAlgorithm::setPreviousControlAlgorithm(ControlAlgorithm* previous){
	previous->next = this;
}

void ControlAlgorithm::setToZero(){
  setDesiredSetpoint(0);
}

void ControlAlgorithm::reset(){
  setToZero();
  resetIncrementalActivation();
}

void ControlAlgorithm::resetStartingParameters(){
  resetIncrementalActivation();
}

void ControlAlgorithm::resetIncrementalActivation(){
  activation_count = 0;
}

void ControlAlgorithm::setGain(double gain){
  this->gain = gain;
}

void ControlAlgorithm::setDesiredSetpoint(double setpoint){
  previous_desired_setpoint = setpoint;
  desired_setpoint = setpoint;
}

ControlAlgorithm* ControlAlgorithm::getNextAlgorithm(){
  return next;
}

void ControlAlgorithm::activate(){
  activation_count++;
}

double ControlAlgorithm::getActivationPercent(){
  return activation_clamp->clamp(activation_count / ACTIVATION_STEP_COUNT);
}

double ControlAlgorithm::getShapingIterations(){
  return shaping_iteration_threshold;
}

void ControlAlgorithm::setShapingIterations(double iterations){
  shaping_iteration_threshold = iterations;
}

ZeroTorqueControl::ZeroTorqueControl(StateID state_id):ControlAlgorithm(state_id){}

double ZeroTorqueControl::getSetpoint(double fsr_percentage, double fsr_max_percentage){
  return 0;
}

bool ZeroTorqueControl::useShapingFunction(){
  return false;
}

ControlAlgorithmType ZeroTorqueControl::getType(){
  return zero_torque;
}

BangBangControl::BangBangControl(StateID state_id):ControlAlgorithm(state_id){}

void BangBangControl::activate(){
  ControlAlgorithm::activate();
  used_setpoint = getActivationPercent() * (desired_setpoint - previous_desired_setpoint) + previous_desired_setpoint;
}

double BangBangControl::getSetpoint(double fsr_percentage, double fsr_max_percentage){
  double new_setpoint = used_setpoint;
  return clamp_setpoint(new_setpoint);
}

bool BangBangControl::useShapingFunction(){
  return true;
}

ControlAlgorithmType BangBangControl::getType(){
  return bang_bang;
}

BalanceControl::BalanceControl(StateID state_id):ControlAlgorithm(state_id){}

double BalanceControl::getSetpoint(double fsr_percentage, double fsr_max_percentage){
  // TODO implement balance control
  return 0;
}

double BalanceControl::getShapingIterations(){
  return 1;
}

bool BalanceControl::useShapingFunction(){
  return false;
}

ControlAlgorithmType BalanceControl::getType(){
  return balance_control;
}

ProportionalControl::ProportionalControl(StateID state_id):ControlAlgorithm(state_id){}
double ProportionalControl::getSetpoint(double fsr_percentage, double fsr_max_percentage){
  double new_setpoint = desired_setpoint * gain * fsr_percentage;
  return clamp_setpoint(new_setpoint);
}

bool ProportionalControl::useShapingFunction(){
  return false;
}

ControlAlgorithmType ProportionalControl::getType(){
  return proportional;
}

ProportionalPivotControl::ProportionalPivotControl(StateID state_id):ControlAlgorithm(state_id){}
double ProportionalPivotControl::getSetpoint(double fsr_percentage, double fsr_max_percentage){
  double new_setpoint = (desired_setpoint) *
    (p_prop[0] * pow(fsr_percentage, 2) + p_prop[1] * (fsr_percentage) + p_prop[2]) / (p_prop[0] + p_prop[1] + p_prop[2]) ;
  return clamp_setpoint(new_setpoint);
}

bool ProportionalPivotControl::useShapingFunction(){
  return false;
}

ControlAlgorithmType ProportionalPivotControl::getType(){
  return pivot_proportional;
}
