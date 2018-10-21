#include "Leg.h"
#include "Pins.h"
#include "Shaping_Functions.h"

Leg::Leg(LegPins* legPins){
  this->foot_fsrs = new FSRGroup(legPins->fsr_pins, legPins->fsr_count);
  this->motor_count = legPins->motor_count;
  this->motors = new Motor*[motor_count];
  for (int i = 0; i < legPins->motor_count; i++){
    this->motors[i] = new Motor(&legPins->motor_pins[i]);
  }
}

double Leg::getBalanceReference(){
  return foot_fsrs->getBalanceReference() * Prop_Gain;
}

void Leg::calibrateFSRs(){
  foot_fsrs->calibrate();
}

void Leg::startTorqueCalibration(){
  for(int i = 0; i < motor_count;i++){
    motors[i]->startTorqueCalibration();
  }
}

void Leg::updateTorqueCalibration(){
  for(int i = 0; i < motor_count;i++){
    motors[i]->updateTorqueCalibration();
  }
}

void Leg::endTorqueCalibration(){
  for(int i = 0; i < motor_count;i++){
    motors[i]->endTorqueCalibration();
  }
}

bool Leg::checkMotorErrors(){
  for(int i = 0; i < motor_count;i++){
    if(motors[i]->hasErrored()){
      return true;
    }
  }
  return false;
}

void Leg::autoKF(){
  for(int i = 0; i < motor_count;i++){
    motors[i]->autoKF(state);
  }
}

void Leg::adjustControl(){
  for(int i = 0; i<motor_count;i++){
    motors[i]->adjustControl(state, state_old, FSR_baseline_FLAG);
  }
}

void Leg::resetStartingParameters(){
  this->N3 = N3;
  this->N2 = N2;
  this->N1 = N1;

  this->activate_in_3_steps = 1;

  this->num_3_steps = 0;

  this->first_step = 1;

  for (int i = 0; i < motor_count; i++){
    motors[i]->resetStartingParameters();
  }
}

void Leg::setZeroIfSteadyState(){
  if (this->flag_1 == 0) {
    this->flag_1 = 1;
    this->time_old_state = this->state;
  }
  if (this->state != this->time_old_state) {
    this->flag_1 = 0;
    this->stateTimerCount = 0;
  } else {
    if (this->stateTimerCount >= 5 / 0.002) {
      if (this->store_N1 == 0) {
        Serial.println("Steady state, setting to 0Nm , Change N1");
        this->set_2_zero = 1;
        this->store_N1 = 1;
        this->activate_in_3_steps = 1;
        this->num_3_steps = 0;
        this->first_step = 1;
        this->start_step = 0;
      }
    } else {
      this->stateTimerCount++;
      if (this->store_N1) {
        this->set_2_zero = 0;
        this->store_N1 = 0;
      }
    }
  }
}

int Leg::determineState(boolean foot_on_ground){
  int new_state;
  if (swing_state_threshold->getState((double) foot_on_ground)){
    new_state = SWING;
  } else {
    new_state = LATE_STANCE;
  }

  if (new_state != this->state){
    this->state_old = this->state;
    this->state = state;
    for(int i = 0; i < motor_count; i++){
      motors[i]->changeState(state);
    }
  }
  return new_state;
}

bool Leg::determine_foot_on_ground(){
  boolean foot_on_fsr = this->motors[0]->p_steps->curr_voltage > this->foot_fsrs->getThreshold();
  return foot_on_fsr;
}

void Leg::applyStateMachine(){

  if (this->set_2_zero){
    switch (this->state) {
    case SWING:
      this->set_2_zero = 0;
      this->One_time_set_2_zero = 1;
      break;
    case LATE_STANCE:
      if (this->One_time_set_2_zero) {
        this->One_time_set_2_zero = 0;
        this->state_old = this->state;
        for(int i = 0; i<motor_count; i++){
          motors[i]->setToZero();
        }
      }
      break;
    }
  }

  bool foot_on_ground = determine_foot_on_ground();
  this->determineState(foot_on_ground);
  ref_step_adj(this);
  for(int i = 0; i < motor_count;i++){
    motors[i]->updateSetpoint(state);
  }

}


void Leg::measureSensors(){
  for(int i = 0; i < motor_count; i++){
    this->motors[i]->measureTorque();
    this->motors[i]->measureError();
  }
  this->foot_fsrs->measureForce();

}

void Leg::takeFSRBaseline(){
  if (FSR_baseline_FLAG){
    for (int i = 0; i < motor_count; i++){
      motors[i]->takeBaseline(state, state_old, &FSR_baseline_FLAG);
    }
  }
}

bool Leg::applyTorque(){
  for(int i = 0; i < motor_count; i++){
    if (!motors[i]->applyTorque(state)){
      state = 9;
      return false;
    }
  }
  return true;
}
