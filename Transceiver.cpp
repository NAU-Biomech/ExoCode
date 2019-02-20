#include "Transceiver.hpp"
#include "Arduino.hpp"
#include "Exoskeleton.hpp"
#include "States.hpp"



Transceiver::~Transceiver(){
}

void MatlabTransceiver::clear(){
  while(dataAvailable()){
    serial->read();
  }
}

bool Transceiver::noDataAvailable(){
  return !dataAvailable();
}

MatlabTransceiver::MatlabTransceiver(TxPort* tx, RxPort* rx){
  serial = new SoftwareSerial(tx->getPin(), rx->getPin());
  serial->begin(115200);
  delete tx;
  delete rx;
}

MatlabTransceiver::~MatlabTransceiver(){
  // Commented command serial delete until software serial allows deletion
  /* delete command_serial; */
}

bool MatlabTransceiver::dataAvailable(){
  return serial->available() > 0;
}

bool MatlabTransceiver::receiveHeader(){
  return true;
}

CommandCode MatlabTransceiver::receiveCommand(){
  return serial->read();
}

bool MatlabTransceiver::receiveFooter(){
  return true;
}

void MatlabTransceiver::receiveData(double* output_data, int doubles_expected){
  if (doubles_expected <= 0){
    return;
  }
  doubles_expected *= sizeof(double);
  char* output_data_raw_form = (char*) output_data;
  for(int i = 0; i < doubles_expected; i ++){
    while (noDataAvailable()){}
    int data = serial->read();
    output_data_raw_form[i] = data;
  }
}

void MatlabTransceiver::sendHeader(){
  serial->write('S');
}

void MatlabTransceiver::sendCommand(CommandCode code){
  serial->write(code);
  serial->write(',');
}

void MatlabTransceiver::sendData(double* data, int doubles_to_send){
  if (doubles_to_send <= 0){
    return;
  }

  char* raw_data = (char*) data;
  for (int i = 0; i < doubles_to_send; i++){
    for(unsigned int j = 0; j < sizeof(double); j++){
      unsigned int d = raw_data[i * sizeof(double) + j];
      serial->write(d);
    }
  }
}

void MatlabTransceiver::sendFooter(){
  serial->write('Z');
  serial->println();
}
