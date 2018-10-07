// This is the code for the Single board Ankle Exoskeleton -> A_EXO_s
//
// FSR sensors retrieve the sensor voltage related to the foot pressure.
// The state machine (Left and Right state machine) identify the participant status depending on the voltage.
// The torque reference is decided by the user (Matlab GUI) and send as reference to the PID control.
// The PID control and data tranmission to the GUI are scheduled by an interrupt.
//
// Sensor can be calibrated by the user and/or saved calibration can be loaded to speed up the setup.
//
// The torque reference can be smoothed by sigmoid functions
// In case of too long steady state the torque reference is set to zero
// In case of new torque reference the torque amount is provided gradually as function of the steps.
//
// Ex: Torque ref = 10N
// 1 step = 0N
// 2 steps = 2N
// 3 steps = 4N
// 4 steps = 6N
// 5 steps = 8N
// 6 steps = 10N
//
// The torque and the shaping function can be adapted as function of the force pressure/Voltage
// and averaged speed/step duration
//
// Several parameters can be modified thanks to the Receive and Transmit functions

#include "Parameters.h"
#include "Board.h"

#include "State_Machine.h"
#include "TimerOne.h"
#include "Auto_KF.h"
#include "IMU.h"
#include "Receive_and_Transmit.h"
#include "Exoskeleton.h"

#include "System.h"

void setup()
{

  setupBoard();

  setupIMU(&bno);

  exo->initialize();

  // Fast torque calibration
  exo->calibrateTorque();

  digitalWrite(LED_PIN, HIGH);

  // set the interrupt
  Timer1.initialize(2000);         // initialize timer1, and set a 10 ms period *note this is 10k microseconds*
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void callback()//executed every 2ms
{

  resetMotorIfError();

  calculate_averages();

  check_FSR_calibration();

  check_Balance_Baseline();

  rotate_motor();

}// end callback

void loop()
{

  if (slowThisDown.check() == 1) // If the time passed is over 1ms is a true statement
  {
    //    start_time_timer = millis();
    if (bluetooth.available() > 0)
    {
      receive_and_transmit();       //Recieve and transmit was moved here so it will not interfere with the data message
    }

    slowThisDown.reset();     //Resets the interval
  }

  if (BnoControl.check()) {
    updateIMU(&bno);
    BnoControl.reset();
  }

  if (stream != 1)
  {
    reset_starting_parameters();
  }// End else
}

void resetMotorIfError() {
  //motor_error true I have an error, false I haven't

  bool motor_error = exo->checkMotorErrors();

  if (stream == 1) {

    if (not(motor_error) && (digitalRead(MOTOR_ENABLE_PIN) == LOW)) {
      digitalWrite(MOTOR_ENABLE_PIN, HIGH);
    }

    if (motor_error && (flag_enable_catch_error == 0)) {
      flag_enable_catch_error = 1;
    }

    if (flag_enable_catch_error) {
      if (time_err_motor == 0) {
        digitalWrite(MOTOR_ENABLE_PIN, LOW);
        time_err_motor_reboot = 0;
      }

      motor_driver_count_err++;
      time_err_motor++;

      //was time_err_motor >= 4
      if (time_err_motor >= 8) {
        digitalWrite(MOTOR_ENABLE_PIN, HIGH);
        time_err_motor_reboot++;
        if (time_err_motor_reboot >= 12) {
          flag_enable_catch_error = 0;
          time_err_motor = 0;
        }
      }

    }// end if flag_enable_catch_error==1;

  }//end stream==1
}

void calculate_averages() {
  exo->measureSensors();
}

void check_FSR_calibration() {

  if (FSR_CAL_FLAG) {
    exo->calibrateFSRs();
  }

  exo->takeFSRBaseline();

}

void check_Balance_Baseline() {
  if (FLAG_BALANCE_BASELINE) {
    Balance_Baseline();
  }
}

void rotate_motor() {

  if (stream == 1)
  {
    if (streamTimerCount >= 5)
    {
      send_data_message_wc();
      streamTimerCount = 0;
    }

    if (streamTimerCount == 1 && flag_auto_KF == 1)
      Auto_KF();

    streamTimerCount++;

    stability_trq = euler.z() - 90;
    stability_trq *= stability_trq_gain;

    exo->applyTorque();

    exo->applyStateMachine();

    exo->setZeroIfSteadyState();

    exo->adjustControl();
  }
}

void reset_starting_parameters() {
  //Reset the starting values
  exo->resetStartingParameters();
}
