#ifndef RECEIVE_AND_TRANSMIT_HEADER
#define RECEIVE_AND_TRANSMIT_HEADER
#include <SoftwareSerial.h>
#include "System.hpp"

const char COMM_CODE_REQUEST_DATA = '?';
const char COMM_CODE_GET_LEFT_ANKLE_SETPOINT = 'D';
const char COMM_CODE_GET_RIGHT_ANKLE_SETPOINT = 'd';
const char COMM_CODE_SET_LEFT_ANKLE_SETPOINT = 'F';
const char COMM_CODE_SET_RIGHT_ANKLE_SETPOINT = 'f';
const char COMM_CODE_START_TRIAL = 'E';
const char COMM_CODE_END_TRIAL = 'G';
const char COMM_CODE_CALIBRATE_TORQUE = 'H';
const char COMM_CODE_GET_LEFT_ANKLE_PID_PARAMS = 'K';
const char COMM_CODE_GET_RIGHT_ANKLE_PID_PARAMS = 'k';
const char COMM_CODE_CALIBRATE_FSR = 'L';
const char COMM_CODE_SET_LEFT_PID_PARAMS = 'M';
const char COMM_CODE_SET_RIGHT_PID_PARAMS = 'm';
const char COMM_CODE_CHECK_BLUETOOTH = 'N';
const char COMM_CODE_CHECK_MEMORY = '<';
const char COMM_CODE_CLEAR_MEMORY = '>';
const char COMM_CODE_SET_LEFT_ANKLE_KF_ = '_';
const char COMM_CODE_SET_RIGHT_ANKLE_KF = '-';
const char COMM_CODE_GET_LEFT_ANKLE_KF = '`';
const char COMM_CODE_GET_RIGHT_ANKLE_KF = '~';
const char COMM_CODE_SET_SMOOTHING_PARAMS = ')';
const char COMM_CODE_GET_SMOOTHING_PARAMS = '(';
const char COMM_CODE_SET_LEFT_ANKLE_FREQ_BASELINE = 'P';
const char COMM_CODE_SET_RIGHT_ANKLE_FREQ_BASELINE = 'p';
const char COMM_CODE_ADJ_LEFT_ANKLE_N3 = 'O';
const char COMM_CODE_ADJ_RIGHT_ANKLE_N3 = 'o';
const char COMM_CODE_GET_LEFT_ANKLE_FSR_THRESHOLD = 'Q';
const char COMM_CODE_GET_RIGHT_ANKLE_FSR_THRESHOLD = 'q';
const char COMM_CODE_SET_LEFT_ANKLE_FSR_THRESHOLD = 'R';
const char COMM_CODE_SET_RIGHT_ANKLE_FSR_THRESHOLD = 'r';
const char COMM_CODE_SET_LEFT_ANKLE_PERC = 'S';
const char COMM_CODE_SET_RIGHT_ANKLE_PERC = 's';
const char COMM_CODE_CLEAN_BLUETOOTH_BUFFER = 'C';
const char COMM_CODE_STOP_LEFT_ANKLE_N3_ADJ = 'T';
const char COMM_CODE_STOP_RIGHT_ANKLE_N3_ADJ = 't';
const char COMM_CODE_STOP_LEFT_ANKLE_TORQUE_ADJ = 'I';
const char COMM_CODE_STOP_RIGHT_ANKLE_TORQUE_ADJ = 'i';
const char COMM_CODE_SAVE_EXP_PARAMS = '!';
const char COMM_CODE_MODIFY_LEFT_ANKLE_ZERO = 'W';
const char COMM_CODE_MODIFY_RIGHT_ANKLE_ZERO = 'X';
const char COMM_CODE_NEG_RIGHT_ANKLE_SIGN = 'w';
const char COMM_CODE_RESORE_RIGHT_ANKLE_SIGN = 'x';
const char COMM_CODE_GET_RIGHT_ANKLE_GAIN = '[';
const char COMM_CODE_SET_RIGHT_ANKLE_GAIN = ']';
const char COMM_CODE_GET_LEFT_ANKLE_GAIN = '{';
const char COMM_CODE_SET_LEFT_ANKLE_GAIN = '}';
const char COMM_CODE_ACTIVATE_PROP_CTRL = '+';
const char COMM_CODE_DEACTIVATE_PROP_CTRL = '=';
const char COMM_CODE_ACTIVATE_AUTO_KF = '.';
const char COMM_CODE_DEACTIVATE_AUTO_KF = ';';
const char COMM_CODE_ACTIVATE_PROP_PIVOT_CTRL = '#';
const char COMM_CODE_DEACTIVATE_PROP_PIVOT_CTRL = '^';
const char COMM_CODE_GET_BASELINE = 'B';
const char COMM_CODE_CALC_BASELINE = 'b';
const char COMM_CODE_CALC_BALANCE_BASELINE = '&';

void send_report(SoftwareSerial* commandSerial);
void receive_data(SoftwareSerial* commandSerial, void* outputDataRawForm, int bytesExpected);
void receive_and_transmit(ExoSystem* system);

#endif
