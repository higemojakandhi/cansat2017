/**
* @file motor.cpp
* @author Kandai Watanabe
* @date Created: 20170420
*/
#include "motor.h"

Motor::Motor(int pinMotorFin, int pinMotorRin){
  _pinMotorFin = pinMotorFin;
  _pinMotorRin = pinMotorRin;
 pinMode(_pinMotorFin, OUTPUT);
 pinMode(_pinMotorRin, OUTPUT);
 digitalWrite(_pinMotorFin, LOW);
 digitalWrite(_pinMotorRin, LOW);
}

Motor::~Motor(){
}


void Motor::setSpeedAt(int v){
  // 正転・逆転どっちか
  if(v<0) v=0;
  if(v>255) v=0;
  digitalWrite(_pinMotorFin, HIGH);
  analogWrite(_pinMotorRin, v);
}

void Motor::stop(){
  breaking();
  digitalWrite(_pinMotorFin, LOW);
  digitalWrite(_pinMotorRin, LOW);
}

void Motor::breaking(){
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, HIGH);
  delay(100);
}
