/**
* @file openlog.cpp
* @author Kandai Watanabe
* @date Created: 20170506
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "openlog.h"
#include <HardwareSerial.h>

//HardwareSerial & OpenLog = Serial1;

Openlog::Openlog(int resetPin){
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  initOpenlog();
}

Openlog::~Openlog(){
  clear();
}

void Openlog::clear(){
}

void Openlog::initOpenlog(){
  Serial1.begin(9600);
  delay(1000);

  digitalWrite(_resetPin, LOW);
  delay(100);
  digitalWrite(_resetPin, HIGH);

  Serial.println("start reading...");
  while(1){
    if(Serial1.available()){
      Serial.println("in while loop");
      if(Serial.read() == '<'){
        break;
      }
    }
  }
}

void Openlog::saveDataOnSD(){
  Serial1.println("Please Log What You Want to Save ...");
}
