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


void Motor::setSpeedAt(int v){
  // digitalWrite(_pinMotorFin, HIGH);
  // digitalWrite(_pinMotorRin, LOW);
  // analogWrite(_pinMotorVref, 100);
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, LOW);
//  String motorvolt;
//  sprintf(motorvolt, "Motor Volt: %03d", 5*v/255);
//  Serial.println(motorvolt);
  analogWrite(_pinMotorVref, v);
}

void Motor::stop(){
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, LOW);
  analogWrite(_pinMotorVref, 0);
  delay(100);
}
