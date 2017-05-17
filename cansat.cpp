/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat(){
  motor = new Motor(MOTOR_PIN, FIN_PIN, RIN_PIN);
}

Cansat::~Cansat(){
  clear();
}

void Cansat::clear(){
  delete motor;
  motor = NULL;
}

void Cansat::init(){

}
