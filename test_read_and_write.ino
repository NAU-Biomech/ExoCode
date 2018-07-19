//#include <EEPROM.h>
//int address_torque = 0;
//int address_FSR = 9;
// start reading from the first byte (address 0) of the EEPROM



int check_torque_bias(int address_torque_l) {
  byte value = EEPROM.read(address_torque_l);
  if (char(value) == 'y') {
    Serial.println(" Torque value is present in memory ");
    return 1;
  }
  Serial.println(" Torque value is not present in memory ");
  return 0;
};

int write_torque_bias(int address_torque_l, double torque_adj) {

  EEPROM.put(address_torque_l, 'y');
  address_torque_l++;
  EEPROM.put(address_torque_l, torque_adj);
  return 1;
}

double read_torque_bias(int address_torque_l) {
  address_torque_l += 1;
  double val_t = 0;
  byte array_values[8];
  byte* p_array = array_values;

  for (int i = 0; i < sizeof(double); i++) {
    *(p_array + i) = EEPROM.read(address_torque_l + i);
  }

  memcpy(&val_t, &array_values, 8);

  return val_t;
}


int clean_torque_bias(int address_torque_l) {
  for ( int i = address_torque_l ; i < (sizeof(double) + sizeof(char) + address_torque_l) ; i++ ) {
    EEPROM.write(i, 0);
  }
  return 1;
}
//-----------------------


int check_FSR_values(int address_FSR_l) {
  byte value = EEPROM.read(address_FSR_l);
  if (char(value) == 'y') {
    Serial.println(" FSR values are present in memory ");
    return 1;
  }
  Serial.println(" FSR values are not present in memory ");
  return 0;
}

int write_FSR_values(int address_FSR_l, double FSR_adj) {

  EEPROM.put(address_FSR_l, 'y');
  address_FSR_l++;
  EEPROM.put(address_FSR_l, FSR_adj);
  return 1;
}

double read_FSR_values(int address_FSR_l) {
  address_FSR_l += 1;
  double val_t = 0;
  byte array_values[8];
  byte* p_array = array_values;

  for (int i = 0; i < sizeof(double); i++) {
    *(p_array + i) = EEPROM.read(address_FSR_l + i);
  }

  memcpy(&val_t, &array_values, 8);

  return val_t;
}

int clean_FSR_values(int address_FSR_l) {

  for ( int i = address_FSR_l ; i < (sizeof(double) + sizeof(char) + address_FSR_l) ; i++ ) {
    EEPROM.write(i, 0);
  }

  return 1;
}

//-----------------
//int address_torque = 0;
//int address_FSR = 9;

//int address_torque = 0;
//int address_FSR = 9;

//void setup() {
//  Serial.begin(9600);
//  while (!Serial) {}
//
//  Serial.println("Communication ready");
////  clean_torque_bias(address_torque);
////  clean_FSR_values(address_FSR);
//
//}
//
//int flag = 1;
//double res = 5;
//double res_2 = 10;
//double new_res = 100;
//
//void loop() {
//  if (flag) {
//
//
//    if (check_torque_bias(address_torque)) {
//      Serial.println("I am reading ");
//      new_res = read_torque_bias(address_torque);
//    } else {
//      Serial.println("I am writing ");
//      write_torque_bias(address_torque, res);
//      new_res = read_torque_bias(address_torque);
//    }
//    Serial.println("New value ");
//    Serial.println(new_res);
//
//
//    if (check_FSR_values(address_FSR)) {
//      Serial.println("I am reading ");
//      new_res = read_FSR_values(address_FSR);
//    } else {
//      Serial.println("I am writing ");
//      write_FSR_values(address_FSR, res_2);
//      new_res = read_FSR_values(address_FSR);
//    }
//    Serial.println("New value ");
//    Serial.println(new_res);
//
//
//
//    flag = 0;
//  }// end if flag
//
//
//}
