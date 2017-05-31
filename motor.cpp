/**
* @file motor.cpp
* @author Kandai Watanabe
* @date Created: 20170420
*/
#include "motor.h"

Motor::Motor(int pinMotor, int pinMotorFin, int pinMotorRin){
  _pinMotor = pinMotor;
  _pinMotorFin = pinMotorFin;
  _pinMotorRin = pinMotorRin;
  pinMode(_pinMotor, OUTPUT);
  pinMode(_pinMotorFin, OUTPUT);
  pinMode(_pinMotorRin, OUTPUT);
}

Motor::~Motor(){
}


void Motor::goStraight(){
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, LOW);
  analogWrite(_pinMotor, 100);
  delay(100);
}

void Motor::stop(){
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, LOW);
  analogWrite(_pinMotor, 0);
  delay(100);
}


