/**
* @file light.cpp
* @author Kandai Watanabe
* @date Created: 20170517
*/
#include "light.h"

Light::Light(int pinLight){
  _pinLight = pinLight;
  pinMode(_pinLight, INPUT);
}

Light::~Light(){
}

/**
* @fn void readLightValue()
* @brief read Light Sensor Value and save it
*/
void Light::readLightValue(){
  _lightValue = analogRead(_pinLight);
  // need some function to save its value
}

/**
* @fn int getLightValue()
* @brief return Light Sensor Value
* @return light Sensor Value
*/
int Light::returnLightValue(){
  return _lightValue;
}
