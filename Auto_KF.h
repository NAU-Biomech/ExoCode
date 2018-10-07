#ifndef AUTO_KF_HEADER
#define AUTO_KF_HEADER
#include "utils.h"

void Auto_KF_motor_Late_stance(Average* error_average, double pid_setpoint, double motor_input);
void Auto_KF_motor_Swing(Average* error_average, double KF, Clamp* kf_clamp);

#endif
