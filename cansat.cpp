/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "cansat.h"

Cansat::Cansat(){
  Serial.begin(9600);
  Serial.println("in Cansat");
  motor = new Motor(MOTOR_PIN, FIN_PIN, RIN_PIN);
//  openlog = new Openlog(RESET_PIN);
  Serial.println("Finished Init");
}

Cansat::~Cansat(){
  clear();
}

void Cansat::clear(){
  delete motor;
//  delete openlog;
  motor = NULL;
//  openlog = NULL;
}

void Cansat::init(){
  
}



