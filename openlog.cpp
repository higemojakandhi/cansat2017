/**
* @file openlog.cpp
* @author Kandai Watanabe
* @date Created: 20170506
*/
#include "openlog.h"

OpenLog::OpenLog(int pinOpenLogReset){
  _serial = NULL;
  _pinOpenLogReset = pinOpenLogReset;
  pinMode(_pinOpenLogReset, OUTPUT);
}

OpenLog::~OpenLog(){
}

void OpenLog::setSerial(HardwareSerial* serial){
  _serial = serial;
  init();
}

void OpenLog::init(){
  digitalWrite(_pinOpenLogReset, LOW);
  delay(100);
  digitalWrite(_pinOpenLogReset, HIGH);
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
