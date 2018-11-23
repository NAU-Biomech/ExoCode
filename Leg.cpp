#include <Arduino.h>
#include "Leg.hpp"
#include "Pins.hpp"
#include "Shaping_Functions.hpp"
#include "Motor.hpp"
#include "IMU.hpp"
#include "Report.hpp"

Leg::Leg(LegPins* legPins){
  this->joint_count = legPins->joint_count;
  this->imu_count = legPins->imu_count;
  this->fsr_group_count = legPins->fsr_group_count;

  this->joints = new Joint*[joint_count];
  this->imus = new IMU*[imu_count];
  this->fsrs = new FSRGroup*[fsr_group_count];

  for (int i = 0; i < legPins->fsr_group_count; i++){
    FSRGroupPins* fsr_group_pins = legPins->fsr_groups_pins[i];
    this->fsrs[i] = new FSRGroup(fsr_group_pins);
  }

  for (int i = 0; i < legPins->joint_count; i++){
    JointPins* joint_pins = legPins->joint_pins[i];
    this->joints[i] = new Joint(joint_pins);
  }

  for (int i = 0; i < legPins->imu_count; i++){
    IMUPins* imu_pins = legPins->imu_pins[i];
    this->imus[i] = new IMU(imu_pins);
  }

  this->foot_fsrs = fsrs[0];
  this->setSign(legPins->leg_sign);
}

void Leg::attemptCalibration(){
  // TODO add any flag dependent calibrations here
}

void Leg::applyControl(){
  this->applyStateMachine();
  this->adjustControl();
}

void Leg::calibrateFSRs(){
  foot_fsrs->calibrate();
}

void Leg::startTorqueCalibration(){
  for(int i = 0; i < joint_count;i++){
    joints[i]->startTorqueCalibration();
  }
}

void Leg::updateTorqueCalibration(){
  for(int i = 0; i < joint_count;i++){
    joints[i]->updateTorqueCalibration();
  }
}

void Leg::endTorqueCalibration(){
  for(int i = 0; i < joint_count;i++){
    joints[i]->endTorqueCalibration();
  }
}

bool Leg::checkMotorErrors(){
  for(int i = 0; i < joint_count;i++){
    if(joints[i]->hasErrored()){
      return true;
    }
  }
  return false;
}

void Leg::resetFSRMaxes(){
  for (int i = 0; i <fsr_group_count;i++){
    fsrs[i]->resetMaxes();
  }
}

void Leg::updateFSRMaxes(){
  for(int i =0; i < fsr_group_count; i++){
    fsrs[i]->updateMaxes();
  }
}

void Leg::adjustJointSetpoints(){
  double FSR_percentage = foot_fsrs->getPercentage();
  double max_FSR_percentage = foot_fsrs->getMaxPercentage();

  for(int i = 0; i < joint_count; i++){
    joints[i]->adjustSetpoint(FSR_percentage, max_FSR_percentage);
  }
}

void Leg::runAutoKF(){
  for(int i = 0; i < joint_count; i++){
    joints[i]->applyAutoKF();
  }
}

void Leg::resetStartingParameters(){
  for (int i = 0; i < joint_count; i++){
    joints[i]->resetStartingParameters();
  }
}

void Leg::adjustShapingForTime(double time){
  for (int i =0; i < joint_count; i++){
    joints[i]->adjustShapingForTime(time);
  }
}

void Leg::setZeroIfSteadyState(){
  if (isSteadyState()){
    setToZero();
  }
}

bool Leg::isSteadyState(){
  return state->getStateTime() > STEADY_STATE_TIMEOUT;
}

void Leg::incrementStepCount(){
  step_count++;
}

void Leg::startIncrementalActivation(){
  this->increment_activation_starting_step = step_count;
}

void Leg::updateIncrementalActivation(){
  double since_activation_step_count = this->step_count - this->increment_activation_starting_step;
  double activation_percent = since_activation_step_count / ACTIVATION_STEP_COUNT;
  for(int i = 0; i < joint_count; i++){
    joints[i]->setTorqueScalar(activation_percent);
  }
}

bool Leg::hasStateChanged(boolean foot_on_ground){
  return  swing_state_threshold->getState((double) foot_on_ground) &&
    state->getStateTime() <= step_time_length / 4;
}

void Leg::changeState(){
  state->changeState();
  state->setContext(this);
}

void Leg::adjustControl(){
  updateIncrementalActivation();
  updateMotorSetpoints();
  this->state->run();
}

void Leg::updateMotorSetpoints(){
  for(int i = 0; i < joint_count;i++){
    joints[i]->updateSetpoint(state->getStateType());
  }
}

bool Leg::determine_foot_on_ground(){
  boolean foot_on_fsr = this->foot_fsrs->getForce() > this->foot_fsrs->getThreshold();
  return foot_on_fsr;
}

void Leg::setZeroIfNecessary(){
  if (this->set_motors_to_zero_torque){
    setToZero();
    this->set_motors_to_zero_torque = false;
  }
}

void Leg::setToZero(){
  for(int i = 0; i<joint_count; i++){
    joints[i]->setToZero();
  }
}

void Leg::applyStateMachine(){
  bool foot_on_ground = determine_foot_on_ground();
  if (this->hasStateChanged(foot_on_ground)){
    changeState();
  } else {
    setZeroIfSteadyState();
  }
}

void Leg::measureSensors(){
  for(int i = 0; i < joint_count; i++){
    this->joints[i]->measureTorque();
    this->joints[i]->measureError();
  }
  this->foot_fsrs->measureForce();
  this->measureIMUs();

}

bool Leg::applyTorque(){
  for(int i = 0; i < joint_count; i++){
    if (!joints[i]->applyTorque(state->getStateType())){
      return false;
    }
  }
  return true;
}

void Leg::calibrateIMUs(){
  for (int i = 0; i < imu_count; i++){
    imus[i]->calibrate();
  }
}

void Leg::measureIMUs(){
  for (int i = 0; i < imu_count; i++){
    imus[i]->measure();
  }
}

void Leg::setSign(int sign){
  if (sign == 0){
    return;
  }

  sign = sign / abs(sign);

  for (int i = 0; i < joint_count; i++){
    joints[i]->setSign(sign);
  }
}

LegReport* Leg::generateReport(){
  LegReport* report = new LegReport(joint_count, fsr_group_count, imu_count);
  fillLocalReport(report);
  for (int i = 0; i < joint_count; i++){
    report->joint_reports[i] = joints[i]->generateReport();
  }
  for (int i = 0; i < fsr_group_count; i++){
    report->fsr_reports[i] = fsrs[i]->generateReport();
  }
  for (int i = 0; i < imu_count; i++){
    report->imu_reports[i] = imus[i]->generateReport();
  }
  return report;
}

void Leg::fillReport(LegReport* report){
  fillLocalReport(report);
  for (int i = 0; i < joint_count; i++){
    joints[i]->fillReport(report->joint_reports[i]);
  }
  for (int i = 0; i < fsr_group_count; i++){
    fsrs[i]->fillReport(report->fsr_reports[i]);
  }
  for (int i = 0; i < imu_count; i++){
    imus[i]->fillReport(report->imu_reports[i]);
  }
}

void Leg::fillLocalReport(LegReport* report){
  report->state = state->getStateType();
}
