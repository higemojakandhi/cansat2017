/**
* @file nineaxis.h
* @author Kandai Watanabe
* @date Created: 20170524
*/

#ifndef _NINEAXIS_H_
#define _NINEAXIS_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include <math.h>
#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>


class NineAxis {
public:
  NineAxis();
  ~NineAxis();
  void init();
  void readNineAxisValue();
  void showNineAxisValue();
  float calcDegree(float a, float b);
  void convertAccel(float* x, float* y, float* z);

  FaBo9Axis fabo_9axis;
  int _pinNineAxis;
  float _ax, _ay, _az;
  float _gx, _gy, _gz;
  float _mx, _my, _mz;
  float _temp;
  float _deg;
};

#endif
