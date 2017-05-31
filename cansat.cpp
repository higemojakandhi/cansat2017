/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat(){
}

Cansat::~Cansat(){
}

void Cansat::setSerial(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio){
  gps.setSerial(serialgps);
  openlog.setSerial(serialopenlog);
//  radio.setSerial(serialradio);
}
