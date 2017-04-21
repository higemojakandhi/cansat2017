/**
* @file Motor.h
* @author Kandai Watanabe
* @date Created: 20170420
* @date Modified: 20170420
*/
#ifndef _MOTOR_H_
#define _MOTOR_H_
// #include <vector>
// #include "~~.h"

class Motor {
public:
  Motor(int motorPin, int finPin, int rinPin);
  ~Motor();
  void goStraight();
  void goBack();
  void turnRight();
  void turnLeft();
  void stop();
  int getMotorPin();
  int getFinPin();
  int getRinPin();

private:
  void clear();
  
  int _motorPin;
  int _finPin;
  int _rinPin;
};

#endif
