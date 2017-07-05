/**
* @file gps.h
* @author Kandai Watanabe
* @date Created: 20170524
*/
#ifndef _GPS_H_
#define _GPS_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"

class Gps {
public:
  Gps();
  ~Gps();
  void setSerial(HardwareSerial* serial);
  void readGpsValue();
  void printGpsValue();

  HardwareSerial* _serial;
  unsigned long _time;
  float _lat;
  float _lon;
  short _satNum;
  float _posAccuracy;
  char _buf[200];
};

#endif
