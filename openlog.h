/**
* @file openlog.h
* @author Kandai Watanabe
* @date Created: 20170506
*/
#ifndef _OPENLOG_H_
#define _OPENLOG_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include <HardwareSerial.h>
#include "cansat.h"

class OpenLog {
public:
  OpenLog(int resetPin);
  ~OpenLog();
  void init(HardwareSerial* serial, Cansat* cansat);
  void saveDataOnSD(unsigned long t);

private:
  void clear();
  void _init();
  
  HardwareSerial* _serial;
  Cansat* _cansat;
  int _resetPin;
};

#endif
