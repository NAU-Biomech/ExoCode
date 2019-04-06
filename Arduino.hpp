#ifndef ARDUINO_HEADER
#define ARDUINO_HEADER

#ifdef ARDUINO

#include <Arduino.h>
#include <i2c_t3.h>
#include <SoftwareSerial.h>
#include <Adafruit_BNO055_t3.h>
#include <utility/imumaths.h>

#else


#ifdef ROS
#include "ros/ros.h"
#include "ArduinoInterface.hpp"
#else
#include <stdint.h>
#include <math.h>

class SoftwareSerial{
public:
  const char* readStr;
  int strLen;
  int charIndex;
public:
  SoftwareSerial(int, int);
  bool begin(int);
  void write(char character);
  void write(const char* str);
  void print(double);
  void print(const char[]);
  void println();
  void println(const char[]);
  void println(double);
  void setReadString(const char* str);

  int read();
  int available();
};
#endif

#include <stdio.h>
#include <stdlib.h>


#define I2C_MASTER 1
#define I2C_PULLUP_EXT 1
#define I2C_RATE_100 1
#define I2C_OP_MODE_ISR 1

enum i2c_pins {I2C_PINS_3_4 = 0,
               I2C_PINS_7_8,
               I2C_PINS_37_38};
enum i2c_bus {WIRE_BUS, WIRE1_BUS};

struct sensors_event_t{
  struct {
    double x;
    double y;
    double z;
  } orientation;
};

class Adafruit_BNO055{
public:
  Adafruit_BNO055(int, int, unsigned int, int, i2c_pins, int, int, int);
  bool begin();
  void getEvent(sensors_event_t*);
  void getCalibration(uint8_t*, uint8_t*, uint8_t*, uint8_t*);
  bool isFullyCalibrated();

};


#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

void delay(double);
double max(double, double);
double min(double, double);
unsigned long millis();
void pinMode(int, int);
void analogReadResolution(int);
void analogWriteResolution(int);
int analogRead(int);
void analogWrite(int, int);
int digitalRead(int);
void digitalWrite(int, int);

extern SoftwareSerial Serial;
#endif

#endif
