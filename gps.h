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
#include <TinyGPS++.h>

class Gps {
public:
  Gps();
  ~Gps();
  void setSerial(HardwareSerial* serial);
  void readGpsValue();
  void convert2meters();

  HardwareSerial* _serial;
  TinyGPSPlus tinygps;
//  unsigned long _time;
  // _lat, _lonの単位は[m] (地球を平面とした時)
  float _lat, _lon;
  short _year, _month, _day;
  short _hour, _minute, _second, _centisecond;
  float _speed;
  float _deg;
  float _alt;
  short _satNum;
  float _posAccuracy;
};

#endif
