/**
* @file openlog.cpp
* @author Kandai Watanabe
* @date Created: 20170506
*/
#include "openlog.h"

OpenLog::OpenLog(int resetPin){
  _serial = NULL;
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
}

OpenLog::~OpenLog(){
  clear();
}

void OpenLog::clear(){
}

void OpenLog::init(HardwareSerial* serial, Cansat* cansat){
  _serial = serial;
  _cansat = cansat;
  _init();
}

void OpenLog::_init(){
  digitalWrite(_resetPin, LOW);
  delay(100);
  digitalWrite(_resetPin, HIGH);
  delay(3000);

  Serial.println("OpenLog Begin!"); _serial->println("OpenLog Begin!");
  while(1){
    if(_serial->available()){
      if(_serial->read() == '<'){
        break;
      }
    }else{
      Serial.println("serial not available"); _serial->println("serial not available");
    }
  }
}

void OpenLog::saveDataOnSD(unsigned long t){
  _serial->println(t);
}
