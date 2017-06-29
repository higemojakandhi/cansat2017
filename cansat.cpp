/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat(int date){
  _date = date;
}

Cansat::~Cansat(){
}

void Cansat::init(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio){
  gps.setSerial(serialgps);
  Serial.print(_date);
  openlog.init(serialopenlog, _date);
  Serial.print(_date+1);
//  radio.setSerial(serialradio);
}

void Cansat::readSensorValues(){
  if(_state==PREPARING){
    light.readLightValue();
  }else{
    gps.readGpsValue();
    nineaxis.readNineAxisValue();
    // xbee.readXbeeValue();
  }
}

void Cansat::isPreparing2Flying(){
  if (io_cansat->state_data == PREPARING && io_cansat->light_data.light_value < PRE2FLY_thre) {
    if (io_cansat->sequence_data.Count_0to1 > Count_0to1_thre) {
      _state=FLYING;
    }
  }else if()
}


void Cansat::saveAllData(){
  String alldata = createSaveDataString();
  openlog.saveDataOnSD(alldata);
}

String Cansat::createSaveDataString(){
  String alldata = "";
  alldata += String(millis()) + ", ";
  alldata += String(nineaxis._deg) + ", ";
  alldata += String(light._lightValue) + ", ";
  alldata += String(gps._lat) + ", ";
  alldata += String(gps._lon) + ", ";
  alldata += String(gps._satNum) + ", ";
  alldata += String(gps._posAccuracy) + ", ";
  alldata += String(nineaxis._gx) + ", ";
  alldata += String(nineaxis._gy) + ", ";
  alldata += String(nineaxis._gz);
  return alldata;
}
