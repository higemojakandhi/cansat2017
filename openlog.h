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

class OpenLog {
public:
  OpenLog(int pinOpenLogReset);
  ~OpenLog();
  void setSerial(HardwareSerial* serial);
  void saveDataOnSD(unsigned long t);

  void init();

  HardwareSerial* _serial;
  int _pinOpenLogReset;
};

#endif
