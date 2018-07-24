void state_machine_LL()
{
  switch (L_state)
  {
    case 1: //Swing
      // This flag enables the "set to zero" procedure for the left ankle.
      // When you're for at least 3 seconds in the same state, the torque reference is set to zero
      if (L_set_2_zero == 1) {
        L_set_2_zero = 0;
        One_time_L_set_2_zero = 1;
      }
      else if ((L_p_steps->curr_voltage > fsr_percent_thresh_Left_Toe * fsr_Left_Combined_peak_ref)) //&& (fsr(fsr_sense_Long) < (fsr_thresh_long * fsr_cal_Long)))
      {
        state_count_LL_13++;
        // if you're in the same state for more than state_counter_th it means that it is not noise
        if (state_count_LL_13 >= state_counter_th)
        {
          sigm_done_LL = true;
          Old_PID_Setpoint_LL = PID_Setpoint_LL;
          if (Previous_Setpoint_Ankle_LL <= Setpoint_Ankle_LL) {

            New_PID_Setpoint_LL = Previous_Setpoint_Ankle_LL + (Setpoint_Ankle_LL - Previous_Setpoint_Ankle_LL) * L_coef_in_3_steps;

          } else {

            New_PID_Setpoint_LL = Previous_Setpoint_Ankle_LL - (Previous_Setpoint_Ankle_LL - Setpoint_Ankle_LL) * L_coef_in_3_steps;

          }

          L_state_old = L_state;
          L_state = 3;
          state_count_LL_13 = 0;
          state_count_LL_31 = 0;
        }
      }

      break;
    case 3: //Late Stance
      if ((L_set_2_zero == 1) && (One_time_L_set_2_zero)) {
        sigm_done_LL = true;
        Old_PID_Setpoint_LL = PID_Setpoint_LL;
        L_state_old = L_state;
        New_PID_Setpoint_LL = 0;
        One_time_L_set_2_zero = 0;
        Previous_Setpoint_Ankle_LL = 0;
        PID_Setpoint_LL = 0;
        Setpoint_Ankle_LL_Pctrl = 0;
      }

      if ((L_p_steps->curr_voltage < (fsr_percent_thresh_Left_Toe * fsr_Left_Combined_peak_ref)))
      {
        state_count_LL_31++;
        if (state_count_LL_31 >= state_counter_th)
        {
          sigm_done_LL = true;
          Old_PID_Setpoint_LL = PID_Setpoint_LL;
          L_state_old = L_state;
          New_PID_Setpoint_LL = 0 * L_coef_in_3_steps;
          L_state = 1;
          state_count_LL_31 = 0;
          state_count_LL_13 = 0;
        }
      }
  }
  // Adjust the torque reference as a function of the step
  L_ref_step_adj();

  if ((Trq_time_volt == 2 || Trq_time_volt == 3) && L_state == 3) {
    PID_Setpoint_LL = Setpoint_Ankle_LL_Pctrl;
    Serial.println("After switch case : ");
    Serial.println(L_coef_in_3_steps_Pctrl);
    Serial.println(Setpoint_Ankle_LL_Pctrl);
    Serial.println(PID_Setpoint_LL);
    Serial.println();
  }
  else {

    if (N1 < 1 || N2 < 1 || N3 < 1) {
      PID_Setpoint_LL = New_PID_Setpoint_LL;
    }
    else {
      // Create the smoothed reference and call the PID
      PID_Sigm_Curve_LL();
    }
    
  }

}
