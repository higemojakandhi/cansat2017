/**
  @file motor.cpp
  @author Kandai Watanabe
  @date Created: 20170420
*/
#include "motor.h"

Motor::Motor(int pinMotorFin, int pinMotorRin) {
  _pinMotorFin = pinMotorFin;
  _pinMotorRin = pinMotorRin;
  pinMode(_pinMotorFin, OUTPUT);
  pinMode(_pinMotorRin, OUTPUT);
  digitalWrite(_pinMotorFin, LOW);
  digitalWrite(_pinMotorRin, LOW);
}

Motor::~Motor() {
}


void Motor::setSpeedAt(int v) {
  // 正転・逆転どっちか
  if (v < 0) v = 0;
  if (v > 255) v = 255;
  _velocity = v;
  analogWrite(_pinMotorFin, v);
  digitalWrite(_pinMotorRin, LOW);
  Serial.print("Motor Speed: "); Serial.println(_velocity);

}

void Motor::goBack(int v) {
  if (v < 0) v = 0;
  if (v > 255) v = 255;
  _velocity=v;
  digitalWrite(_pinMotorFin, LOW);
  analogWrite(_pinMotorRin, v);
}

void Motor::stopSlowly() {
  if (_velocity != 0) {
    for (int i = 0; i < 25; i++) {
      analogWrite(_pinMotorFin, 255 - 10 * i);
      digitalWrite(_pinMotorRin, LOW);
      delay(100);
    }
    _velocity=0;
    breaking();
  }
  digitalWrite(_pinMotorFin, LOW);
  digitalWrite(_pinMotorRin, LOW);
  Serial.print("Motor Speed: "); Serial.println(_velocity);
}

void Motor::stop() {
  _velocity = 0;
  breaking();
  digitalWrite(_pinMotorFin, LOW);
  digitalWrite(_pinMotorRin, LOW);
  Serial.print("Motor Speed: "); Serial.println(_velocity);
}

void Motor::breaking() {
  digitalWrite(_pinMotorFin, HIGH);
  digitalWrite(_pinMotorRin, HIGH);
  delay(100);
}
