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
  Light(int lightPin);
  ~Light();
  void readLightValue();
  int getLightValue();

private:
  int _lightValue;
  int _lightPin;
};

#endif
