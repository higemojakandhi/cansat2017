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
  void init(HardwareSerial* serial);
  void readGpsValue();
  void saveGpsValue();
  void showGpsValue();

private:
  HardwareSerial* _serial;
  float _time;
  float _lat;
  float _lon;
  char _buf[200];
};

#endif
