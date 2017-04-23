/**
* @file motor.cpp
* @author Kandai Watanabe
* @date Created: 20170420
* @date Modified: 20170420
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "motor.h"

Motor::Motor(int motorPin, int finPin, int rinPin){
  _motorPin = motorPin;
  _finPin = finPin;
  _rinPin = rinPin;
  pinMode(_motorPin, OUTPUT);
  pinMode(_finPin, OUTPUT);
  pinMode(_rinPin, OUTPUT);
}

Motor::~Motor(){
  clear();
}

void Motor::clear(){
}

void Motor::goStraight(){
  digitalWrite(_finPin, HIGH);
  digitalWrite(_rinPin, LOW);
  analogWrite(_motorPin, 100);
  delay(100);
}

void Motor::goBack(){
}

void Motor::turnLeft(){

}

void Motor::turnRight(){

}

void Motor::stop(){
  
}

int Motor::getMotorPin(){
  return _motorPin;
}

int Motor::getFinPin(){
  return _finPin;
}

int Motor::getRinPin(){
  return _rinPin;
}
