/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CANSAT_H_
#define _CANSAT_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "constant.h" //ALL CONSANTS ARE HERE!!! ex) Pin Number
#include "motor.h"
#include "light.h"
#include "gps.h"
#include "nineaxis.h"
#include "openlog.h"

class Cansat {
public:
  // Initialization (Constructor and Destructor)
  Cansat(int date);
  ~Cansat();
  void init(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio);
  String createSaveDataString();
  void saveAllData();
  void readSensorValues();

  void isPreparing2Flying();

  // Objects
  Motor leftMotor = Motor(PIN_LEFT_MOTOR_VREF, PIN_LEFT_MOTOR_FIN, PIN_LEFT_MOTOR_RIN);
  Motor rightMotor = Motor(PIN_RIGHT_MOTOR_VREF, PIN_RIGHT_MOTOR_FIN, PIN_RIGHT_MOTOR_RIN);
  Light light = Light(PIN_LIGHT);
  Gps gps;
  NineAxis nineaxis;
  OpenLog openlog = OpenLog(PIN_OPENLOG_RESET);

  // Variables to save
  int _date;
  int _state;
  // Functions
};

#endif
