/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CANSAT_H_
#define _CANSAT_H_
#include "motor.h"
//#include "openlog.h"

#define MOTOR_PIN 8
#define FIN_PIN 40
#define RIN_PIN  30
//#define RESET_PIN 4

class Cansat {
public:
  Cansat();
  ~Cansat();
  void init();
  Motor* motor;
//  Openlog* openlog;

private:
  void clear();
};

#endif


