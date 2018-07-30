#ifndef BOARD_SETTINGS_HEADER
#define BOARD_SETTINGS_HEADER

#ifdef IMU_BOARD
#include <i2c_t3.h>
const i2c_pins IMU_SLOT_1_PINS = I2C_PINS_3_4;
const i2c_pins IMU_SLOT_2_PINS = I2C_PINS_7_8;
const i2c_pins IMU_SLOT_3_PINS = I2C_PINS_37_38;

const unsigned int RX1_PIN = 0;
const unsigned int TX1_PIN = 1;

const unsigned int FSR_SENSE_RIGHT_HEEL_PIN = A12;
const unsigned int FSR_SENSE_RIGHT_TOE_PIN = A13;
const unsigned int FSR_SENSE_LEFT_TOE_PIN = A14;
const unsigned int FSR_SENSE_LEFT_HEEL_PIN = A15;

const unsigned int TORQUE_SENSOR_RIGHT_ANKLE_PIN = A6;
const unsigned int TORQUE_SENSOR_LEFT_ANKLE_PIN = A0;

const unsigned int MOTOR_LEFT_ANKLE_PIN = A21;
const unsigned int MOTOR_RIGHT_ANKLE_PIN = A22;

const unsigned int LED_PIN = 13;

const unsigned int MOTOR_ENABLE_PIN = A3;

const unsigned int WHICH_LEG_PIN = 15;

const unsigned int MOTOR_ERROR_LEFT_ANKLE_PIN = 6;
const unsigned int MOTOR_ERROR_RIGHT_ANKLE_PIN = 7;

const i2c_pins IMU_1_PINS = IMU_SLOT_2_PINS;
#endif

#ifdef TWO_LEG_BOARD
const unsigned int RX1_PIN = 0;
const unsigned int TX1_PIN = 1;

const unsigned int FSR_SENSE_RIGHT_HEEL_PIN = A12;
const unsigned int FSR_SENSE_RIGHT_TOE_PIN = A13;
const unsigned int FSR_SENSE_LEFT_TOE_PIN = A14;
const unsigned int FSR_SENSE_LEFT_HEEL_PIN = A15;

const unsigned int TORQUE_SENSOR_RIGHT_ANKLE_PIN = A18;
const unsigned int TORQUE_SENSOR_LEFT_ANKLE_PIN = A19;

const unsigned int MOTOR_LEFT_ANKLE_PIN = A21;
const unsigned int MOTOR_RIGHT_ANKLE_PIN = A22;

const unsigned int LED_PIN = 13;

const unsigned int MOTOR_ENABLE_PIN = 22;

const unsigned int WHICH_LEG_PIN = 15;

const unsigned int MOTOR_ERROR_LEFT_ANKLE_PIN = 6;
const unsigned int MOTOR_ERROR_RIGHT_ANKLE_PIN = 7;
#endif

#endif
