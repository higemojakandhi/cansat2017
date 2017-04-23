/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
* @date Modified: 2017043
*/
#ifndef _CANSAT_H_
#define _CANSAT_H_
// #include <vector>
// #include "~~.h"
#include "motor.h"

#define MOTOR_PIN 8
#define FIN_PIN 40
#define RIN_PIN  30

class Cansat {
public:
  Cansat();
  ~Cansat();
  Motor* motor;

private:
  void clear();
};

#endif
