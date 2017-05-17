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


class Cansat {
public:
  Cansat();
  ~Cansat();
  void init();
  Motor* motor;
  Light light = Light(LIGHT_PIN);

private:
  void clear();
};

#endif
