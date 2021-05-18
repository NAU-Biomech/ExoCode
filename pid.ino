
// In the pid function there's a check on torque reading. If the torque measured is >25 for 10 times it means we have a problem with the cable and we stop the system.
// Changing the number 10 we increase or decrease the sensitivity of the system to false positives at the same time we introduce a delay in the stopping action.
// if the torque measured <25 the counter is reset.

void pid(Leg* leg, double input) {
  if (DEBUG) {Serial.println("In pid(Leg*, double)");}
  if (!CURRENT_CONTROL) {
    if (DEBUG) {Serial.println("In !CURRENT_CONTROL if");}
    if ((abs(input) > 35)) //Was 25, increased to accomodate large exo
    {
      if (DEBUG) {Serial.println("abs(input)>35");}
      leg->torque_error_counter++;
      if (leg->torque_error_counter >= 10) {
        if (DEBUG) {Serial.println("torque_error_counter >= 10");}
        //leg->KF = 0;
        double old_L_state_L = leg->state;
        leg->state = 9;
        if (DEBUG) {Serial.println("send_data_message_wc()");}
        send_data_message_wc();

        if (DEBUG) {Serial.println("onoff low, stream zero, LED_PIN low, leg state old, counter 0");}
        digitalWrite(onoff, LOW);
        stream = 0;
        digitalWrite(LED_PIN, LOW);
        leg->state = old_L_state_L;
        leg->torque_error_counter = 0;
      }

    }//abs(input) > 35
    if (DEBUG) {Serial.println("End abs(input) > 35");}
  }//!CURRENT_CONTROL

  if (CURRENT_CONTROL && leg->PID_Setpoint != 0 && MotorParams != 100 && leg->state == 3) { //Simple Open-Loop Control
    if (DEBUG) {Serial.println("In simple open loop");}
    //leg->Vol = ((leg->PID_Setpoint/(TrqConstant * GearRatio * PulleyRatio * MotorEff * GearboxEff))/NomCurrent*2048) + leg->zero; //Setpoint/(Motor torque constant, gear reduction, pulley reduction, motor eff, gearbox eff)
    //leg->Vol = (0.37293*(leg->PID_Setpoint))/NomCurrent*2048.0; //Regression control, torque only
    leg->Vol = (0.275 * (leg->PID_Setpoint)) / NomCurrent * 2048.0;
    if (Control_Mode == 6 && leg->state == 3) {
      leg->Vol = -leg->Vol;
    }
    if (DEBUG) {Serial.println("End simple open loop");}
  } else if (CURRENT_DIAGNOSTICS && MotorParams != 100) { //Diagnostics Mode
    if (DEBUG) {Serial.println("In diganostics mode");}
    if (leg->Dorsi_Setpoint_Ankle == 0) {
      leg->Vol = leg->Setpoint_Ankle / NomCurrent * 2048.0;
    } else {
      leg->Vol = leg->Dorsi_Setpoint_Ankle / NomCurrent * 2048.0;
    }
    if (DEBUG) {Serial.println("End diagnostics mode");}
  } else if (MODEL_CONTROL && MotorParams != 100) {
    if (DEBUG) {Serial.println("In model control and motorparams != 100");}
    leg->Vol = (0.34284 * (leg->PID_Setpoint) + 0.023564 * (leg->AverageSpeed) + 0.0043038 * (leg->PID_Setpoint * leg->AverageSpeed)) / NomCurrent * 2048; //Regression control, complex model
    if (Control_Mode == 6 && leg->state == 3) {
      leg->Vol = -leg->Vol;
    }
  } else { //Closed-Loop Proportional Control
    if (DEBUG) {Serial.println("In closed loop p-ctrl");}
    if (Control_Mode == 6 && leg->state == 3) {
      leg->PID_Setpoint = -leg->PID_Setpoint;
    }
    leg->Input = input;
    leg->pid.PID::Compute();
    leg->Vol = leg->Output; //need to map
  }

  leg->Vol = leg->Vol + leg->zero; // Modify the span such that the PWM value is from 0 to 4096.0 instead of -2048.0 to 2048.0

  analogWrite(leg->motor_ankle_pin, leg->Vol); //0 to 4096 writing for motor to get Input
  if (DEBUG) {Serial.println("End flag_auto_KF if");}
} 
