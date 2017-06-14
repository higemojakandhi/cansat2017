/**
* @file motor.cpp
* @author Kandai Watanabe
* @date Created: 20170420
*/
#include "motor.h"

Motor::Motor(int pinMotorVref, int pinMotorFin, int pinMotorRin){
  _pinMotorVref = pinMotorVref;
  _pinMotorFin = pinMotorFin;
  _pinMotorRin = pinMotorRin;
  pinMode(_pinMotorVref, OUTPUT);
  pinMode(_pinMotorFin, OUTPUT);
  pinMode(_pinMotorRin, OUTPUT);
}

Motor::~Motor(){
}


void Motor::goStraight(int v){
  // digitalWrite(_pinMotorFin, HIGH);
  // digitalWrite(_pinMotorRin, LOW);
  // analogWrite(_pinMotorVref, 100);
  
  digitalWrite(_pinMotorFin, LOW);
  analogWrite(_pinMotorRin, v);
  delay(100);
}

void Motor::stop(){
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, LOW);
  analogWrite(_pinMotorVref, 0);
  delay(100);
}
