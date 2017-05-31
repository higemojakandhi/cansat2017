/**
* @file light.h
* @author Kandai Watanabe
* @date Created: 20170517
*/
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"

class Light {
public:
  Light(int pinLight);
  ~Light();
  void readLightValue();
  int getLightValue();

  int _lightValue;
  int _pinLight;
};

#endif
