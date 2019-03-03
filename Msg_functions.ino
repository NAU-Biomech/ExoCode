
void send_data_message_wc() //with COP
{



  bluetooth.print('S');
  bluetooth.print(',');

  // RIGHT
  bluetooth.print(right_leg->sign * right_leg->Average_Trq); //1
  bluetooth.print(',');
  bluetooth.print(right_leg->state); //2
  bluetooth.print(',');
  bluetooth.print(right_leg->sign * right_leg->PID_Setpoint); //3
  bluetooth.print(',');

  if (FLAG_TWO_TOE_SENSORS) {
    bluetooth.print(right_leg->fsr_percent_thresh_Toe * right_leg->fsr_Combined_peak_ref); //4
    bluetooth.print(',');
    bluetooth.print(right_leg->FSR_Combined_Average); //5
    bluetooth.print(',');
  } else {
    if (FLAG_BALANCE) {
      bluetooth.print(right_leg->FSR_Toe_Average); //4
      bluetooth.print(',');
      bluetooth.print(right_leg->FSR_Heel_Average); //5
      bluetooth.print(',');
    } else {
      bluetooth.print(right_leg->fsr_percent_thresh_Toe * right_leg->fsr_Toe_peak_ref); //4
      bluetooth.print(',');
      bluetooth.print(right_leg->FSR_Toe_Average); //5
      bluetooth.print(',');
    }
  }



  //  if (FLAG_TWO_TOE_SENSORS) {
  //    bluetooth.print(right_leg->fsr_percent_thresh_Toe * right_leg->fsr_Combined_peak_ref);
  //    bluetooth.print(',');
  //    if (FLAG_BALANCE) {
  //      bluetooth.print(right_leg->FSR_Toe_Average);
  //      bluetooth.print(',');
  //    } else {
  //      bluetooth.print(right_leg->FSR_Combined_Average);
  //      bluetooth.print(',');
  //    }
  //  } else {
  //    bluetooth.print(right_leg->fsr_percent_thresh_Toe * right_leg->fsr_Toe_peak_ref);
  //    bluetooth.print(',');
  //    bluetooth.print(right_leg->FSR_Toe_Average);
  //    bluetooth.print(',');
  //  }


  // LEFT
  bluetooth.print(left_leg->sign * left_leg->Average_Trq);
  bluetooth.print(',');
  bluetooth.print(left_leg->state);
  bluetooth.print(',');
  bluetooth.print(left_leg->sign * left_leg->PID_Setpoint);
  bluetooth.print(',');

  if (FLAG_TWO_TOE_SENSORS) {
    bluetooth.print(left_leg->fsr_percent_thresh_Toe * left_leg->fsr_Combined_peak_ref);
    bluetooth.print(',');
    bluetooth.print(left_leg->FSR_Combined_Average);
    bluetooth.print(',');
  } else {
    if (FLAG_BALANCE) {
      bluetooth.print(left_leg->FSR_Toe_Average);
      bluetooth.print(',');
      bluetooth.print(left_leg->FSR_Heel_Average);
      bluetooth.print(',');
    } else {
      bluetooth.print(left_leg->fsr_percent_thresh_Toe * left_leg->fsr_Toe_peak_ref);
      bluetooth.print(',');
      bluetooth.print(left_leg->FSR_Toe_Average);
      bluetooth.print(',');
    }
  }

  //
  //
  //
  //
  //  if (FLAG_TWO_TOE_SENSORS) {
  //    bluetooth.print(left_leg->fsr_percent_thresh_Toe * left_leg->fsr_Combined_peak_ref);
  //    bluetooth.print(',');
  //    if (FLAG_BALANCE) {
  //      bluetooth.print(left_leg->FSR_Toe_Average);
  //      bluetooth.print(',');
  //    } else {
  //      bluetooth.print(left_leg->FSR_Combined_Average);
  //      bluetooth.print(',');
  //    }
  //  } else {
  //    bluetooth.print(left_leg->fsr_percent_thresh_Toe * left_leg->fsr_Toe_peak_ref);
  //    bluetooth.print(',');
  //    bluetooth.print(left_leg->FSR_Toe_Average);
  //    bluetooth.print(',');
  //  }



  //  bluetooth.print(left_leg->Time_error_counter); //SIG1
  //  bluetooth.print(',');
  //  bluetooth.print(right_leg->Time_error_counter); //SIG2
  //  bluetooth.print(',');

  //  bluetooth.print((left_leg->FSR_Heel_Average)); //SIG1

  //  bluetooth.print((LED_BT_Voltage)); //SIG1
  //  bluetooth.print(',');
  //  bluetooth.print((right_leg->FSR_Heel_Average)); //SIG2
  //  bluetooth.print(',');
  if (FLAG_BALANCE) {
    bluetooth.print(left_leg->COP_Foot_ratio); //SIG1
    bluetooth.print(',');
    bluetooth.print(right_leg->COP_Foot_ratio); //SIG2
    bluetooth.print(',');
  } else if (FLAG_BIOFEEDBACK) {
    //    (pot(leg->Potentiometer_pin) + leg->Biofeedback_bias)
    bluetooth.print(pot(left_leg->Potentiometer_pin) + left_leg->Biofeedback_bias); //SIG1
    bluetooth.print(',');
    bluetooth.print(pot(right_leg->Potentiometer_pin) + right_leg->Biofeedback_bias); //SIG2
    bluetooth.print(',');

  }
  else {
    bluetooth.print((LED_BT_Voltage)); //SIG1
    bluetooth.print(',');
    bluetooth.print((right_leg->FSR_Heel_Average)); //SIG2
    bluetooth.print(',');
  }
  //    bluetooth.print(left_leg->FSR_Toe_Average); //SIG3
  //    bluetooth.print(',');
  //    bluetooth.print(right_leg->FSR_Toe_Average); //SIG4
  if (FLAG_BIOFEEDBACK) {
    bluetooth.print(left_leg->Heel_Strike_baseline); //SIG3
    bluetooth.print(',');
    bluetooth.print(Freq); //SIG4
  }
  else {
    bluetooth.print(left_leg->COP); //SIG3
    bluetooth.print(',');
    bluetooth.print(right_leg->COP); //SIG4
  }

  //  bluetooth.print(counter_msgs); //SIG3
  //  bluetooth.print(',');
  //  bluetooth.print(millis() / 1000); //SIG4

  bluetooth.print(',');
  bluetooth.println('Z');
}

void send_command_message(char command_char, double* data_point, int number_to_send)
{
  bluetooth.print('S');
  bluetooth.print(command_char);
  bluetooth.print(',');
  for (int message_iterator = 0; message_iterator < number_to_send; message_iterator++)
  {
    bluetooth.print(*(data_point + message_iterator));
    bluetooth.print(',');
  }
  bluetooth.println('Z');
}
