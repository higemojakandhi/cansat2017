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
  Cansat();
  ~Cansat();
  void setSerial(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio);

  // Objects
  Motor motor = Motor(PIN_MOTOR, PIN_MOTOR_FIN, PIN_MOTOR_RIN);
  Light light = Light(PIN_LIGHT);
  Gps gps;
  NineAxis nineaxis;
  OpenLog openlog = OpenLog(PIN_OPENLOG_RESET);

  // Variables to save

  // Functions
};

#endif
