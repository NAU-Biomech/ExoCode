#include "Motor.h"
#include "utilites.h"

Motor::Motor(int motor_pin, int torque_sensor_pin, int error_pin){
  this.motor_pin = motor_pin;
  this.torque_sensor_pin = torque_sensor_pin;
  this.motor_error_pin = error_pin;
}

void Motor::writeToMotor(int value){
  leg->Vol = leg->Output + leg->zero; //need to map
// TODO Find a better way to implement this preprocessor instruction
#ifdef QUAD_BOARD
  leg->Vol = leg->Vol * 0.8 + 0.1 * 4096;
#endif
  analogWrite(leg->motor_ankle_pin, leg->Vol); //0 to 4096 writing for motor to get Input

}

bool Motor::applyTorque(int state){
  double torque = averaged_torque;
  PID* pid;
  double PID_ref;

  //TODO Test IMU balance control
  if (IMU_ENABLED && state == LATE_STANCE && Trq_time_volt == 2) {
    meas_IMU = clamp(meas_IMU,-45,45);
    PID_Setpoint = 0;
    Input = meas_IMU * Prop_Gain;
    pid = &(balance_pid);
  } else {
    PID_ref = PID_Setpoint;
    Input = torque;
    pid = &(ankle_pid);

    if ((abs(torque) > 25))
    {
      leg->KF = 0;
      double old_L_state_L = leg->state;
      leg->state = 9;
      send_data_message_wc();

      return false;

    }
  }

  pid->Compute_KF(leg->KF);

  //This can be used as alternative to the previous gain (see up)
  if (IMU_ENABLED && leg->state == LATE_STANCE && Trq_time_volt == 2) {
    leg->Output *= leg->Prop_Gain;
    if (leg->Output >= 1500) leg->Output = 1500;
    if (leg->Output <= -1500) leg->Output = -1500;
  }

  writeToMotor(Output);
}

double Motor::measureRawTorque(){
  double Torq = 56.5 / (2.1) * (analogRead(this.torque_sensor_pin) * (3.3 / 4096) - this.torque_calibration_value);
  return -Torq; // TODO Check if negative is necessary
}

void Motor::measureError(){
  inErrorState = digitalRead(err_pin);
}

void Motor::measureTorque(){

    double average = 0;

    for (int i = dim - 1; i >= 1; i--) {
      torque_measurements[i] = torque_measurements[i - 1];
      average += torque_measurements[j - 1];
    }

    torque_measurements[0] = this.getRawTorque();

    average += torque_measurements[0];
    averaged_torque = average / dim;
  }

  double Motor::getTorque(){
    return averaged_torque;
  }

  bool Motor::hasErrored(){
    return inErrorState;
  }
