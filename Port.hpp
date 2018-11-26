#ifndef PORT_HEADER
#define PORT_HEADER

class Port{
private:
  unsigned int pin;
protected:
  unsigned int getPin();
public:
  Port(unsigned int pin);
};

class InputPort:public Port{
public:
  InputPort(unsigned int pin);
  virtual double read() = 0;
};

class AnalogInputPort: public InputPort{
private:
  int resolution;
public:
  double read();
  AnalogInputPort(unsigned int pin, unsigned int resolution_bits);
};

class DigitalInputPort: public InputPort{
public:
  double read();
  DigitalInputPort(unsigned int pin);
};

class OutputPort: public Port{
private:
  int resolution;
public:
  virtual void write(double value) = 0;
  OutputPort(unsigned int pin);
};

class AnalogOutputPort: public OutputPort{
private:
  int resolution;
public:
  void write(double value);
  AnalogOutputPort(unsigned int pin, unsigned int bit_resolution);
};

class DigitalOutputPort: public OutputPort{
public:
  void write(double value);
  DigitalOutputPort(unsigned int pin);
};

class PwmOutputPort: public AnalogOutputPort{
public:
  void write(double value);
  PwmOutputPort(unsigned int pin, unsigned int resolution_bits);
};

class PortFactory{
public:
  virtual InputPort* createDigitalInputPort(unsigned int pin) = 0;
  virtual InputPort* createAnalogInputPort(unsigned int pin, unsigned int resolution_bits) = 0;
  virtual OutputPort* createDigitalOutputPort(unsigned int pin) = 0;
  virtual OutputPort* createAnalogOutputPort(unsigned int pin, unsigned int resolution_bits) = 0;
  virtual OutputPort* createPwmOutputPort(unsigned int pin, unsigned int resolution_bits) = 0;
};

class ArduinoPortFactory:public PortFactory{
  InputPort* createDigitalInputPort(unsigned int pin);
  InputPort* createAnalogInputPort(unsigned int pin, unsigned int resolution_bits);
  OutputPort* createDigitalOutputPort(unsigned int pin);
  OutputPort* createAnalogOutputPort(unsigned int pin, unsigned int resolution_bits);
  OutputPort* createPwmOutputPort(unsigned int pin, unsigned int resolution_bits);
};

#endif
