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
#include <MPU9250_RegisterMap.h>
#include <SparkFunMPU9250-DMP.h>


class NineAxis {
public:
  NineAxis();
  ~NineAxis();
  void init();
  void readNineAxisValue();
  void convertAccel(float* x, float* y, float* z);

  MPU9250_DMP imu;
  float _accelX, _accelY, _accelZ; // m/s^2
  float _gyroX, _gyroY, _gyroZ; // degree per second
  float _magX, _magY, _magZ; // micro Tesla
  float _pitch, _roll, _yaw; //degree
  float _deg; // degree
};

#endif
