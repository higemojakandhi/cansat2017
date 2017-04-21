/**
* @file cansat2017.ino
* @brief CanSat Project 2017
* @author Kandai Watanabe
* @date Created: 20170420
* @date Modified: 20170420
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "motor.h"

int MOTOR_PIN = 8;
int FIN_PIN = 40;
int RIN_PIN = 30;

Motor mymotor(MOTOR_PIN, FIN_PIN, RIN_PIN);
void setup() {
  Serial.begin(9600);
  Serial.println("Begin!");
}

void loop() {
  mymotor.goStraight();
  Serial.println(mymotor.getMotorPin());
}
