/**
* @file radio.h
* @author Kandai Watanabe
* @date Created: 20170725
*/
#ifndef _RADIO_H_
#define _RADIO_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include <HardwareSerial.h>
#include <XBee.h>

class Radio {
public:
  Radio();
  ~Radio();
  void setSerial(HardwareSerial* serial);
  void send(String s);

  XBee xbee = XBee();
  HardwareSerial* _serial;
};

#endif
