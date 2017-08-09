/**
* @file motor.h
* @author Kandai Watanabe
* @date Created: 20170421
*/
#ifndef _MOTOR_H_
#define _MOTOR_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"

class Motor {
public:
  Motor(int pinMotorFin, int pinMotorRin);
  ~Motor();
  void setSpeedAt(int v);
  void goBack(int v);
  // 物理的に回路を離す
  void stop();
  void stopSlowly();
  // 電圧を加えた続けてブレーキ
  void breaking();

  int _velocity;
  int _pinMotorFin;
  int _pinMotorRin;
};

#endif
