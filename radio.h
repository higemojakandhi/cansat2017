/**
  @file radio.h
  @author Kandai Watanabe
  @date Created: 20170725
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
    void getData();
    void send(String s);

    String receiveString;
    String stringData;
    int intData;
    int Data;
    String data1;
    String data2;
    int intData1;
    int intData2;
    int moduleData1;
    int moduleData2;
    int stateData;
    int lastState;                                                                                                                                                                                                                                                                     ;

    XBee xbee = XBee();
    HardwareSerial* _serial;
    XBeeResponse response = XBeeResponse();
    ZBRxResponse rx = ZBRxResponse();

};

#endif
