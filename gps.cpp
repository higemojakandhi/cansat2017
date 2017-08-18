/**
* @file gps.cpp
* @author Kandai Watanabe
* @date Created: 20170524
*/
#include "gps.h"

Gps::Gps(){
  _serial=NULL;
  _lat=_lon=0;
  _year=_month=_day=0;
  _hour=_minute=_second=_centisecond=0;
  _speed=0;
  _deg=0;
  _alt=0;
  _satNum=0;
  _posAccuracy=0;
}

Gps::~Gps(){
  _serial=NULL;
}

void Gps::setSerial(HardwareSerial* serial){
  _serial = serial;
  while(_serial->available()>0){
    char c = _serial->read();
    Serial.print(c);
    tinygps.encode(c);
    if(tinygps.date.isValid()){
      _year = tinygps.date.year();
      _month = tinygps.date.month();
      _day = tinygps.date.day();
    }
  }
  Serial.println("");
}

void Gps::readGpsValue(){
  while(_serial->available()>0){
    char c = _serial->read();
    Serial.print(c);
    tinygps.encode(c);
    if(tinygps.location.isValid()){
      _lon = tinygps.location.lng();
      _lat = tinygps.location.lat();
    }
    if(tinygps.time.isValid()){
      _hour = tinygps.time.hour();
      _minute = tinygps.time.minute();
      _second = tinygps.time.second();
      _centisecond = tinygps.time.centisecond();
    }
    if(tinygps.speed.isValid()){
      _speed = tinygps.speed.mps();
    }
    if(tinygps.course.isValid()){
      _deg = tinygps.course.deg();
    }
    _alt = tinygps.altitude.meters();
    _satNum = tinygps.satellites.value();
    _posAccuracy = tinygps.hdop.value();
  }
  Serial.println(" ");

  if (millis() > 5000 && tinygps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

