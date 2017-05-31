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
  Motor(int pinMotor, int pinMotorFin, int pinMotorRin);
  ~Motor();
  void goStraight();
  void stop();
  
  int _pinMotor;
  int _pinMotorFin;
  int _pinMotorRin;
};

#endif
