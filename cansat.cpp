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

void Cansat::judgeInCarrier(){
  int countLoop=0;
  if (_state==PREPARING){
    if(light._lightValue < PRE2FLY_THRE) {
      countLoop++;
      if (countLoop > COUNT_PRE2FLY_LOOP_THRE) _state=FLYING;
    }else{
      countLoop=0;
    }
  }
}

void Cansat::judgeOutOfCarrier(){
  int countLoop=0;
  if(_state==FLYING){
    if(light._lightValue > FLY2DROP_THRE){
      countLoop++;
      if(countLoop > COUNT_FLY2DROP_LOOP_THRE) _state=DROPPING;
    }else{
      countLoop=0;
    }
  }
}

void Cansat::judgeLanding(){

}

void Cansat::judgeReleasing(){
  if(_state==LANDING){
    digitalWrite(PIN_RELEASING, HIGH);
    double currentReleasingTime = millis();
    if (currentReleasingTime - _startReleasingTime > RELEASING_TIME_THRE){
      digitalWrite(PIN_RELEASING, LOW);
      _state=RUNNING;
      _startRunningTime = millis();
    }
  }
}

void Cansat::judgeIdling(){
}

void Cansat::judgeStucking(){
  /* スタック検知用に5s前のGPS座標を保存し，現時刻と比較 */
  double currentGpsPollingTime = millis();
  if(_preGpsPollingTime==0){
    _preGpsPollingTime=millis();
  }else if(_preGpsPollingTime!=0 && currentGpsPollingTime-_preGpsPollingTime > 20000 ){
    _pre20sGpsLat = gps._lat;
    _pre20sGpsLon = gps._lon;
    _preGpsPollingTime = 0;
  }

  /* RUNNING から STUCK に陥る時の判断 */
  if(abs(_pre20sGpsLat-gps._lat)==0 && abs(_pre20sGpsLon-gps._lon)==0) _state=STUCKING;

  /* STUCK から RUNNING への判断 */
  if(abs(_pre20sGpsLat-gps._lat)!=0 || abs(_pre20sGpsLon-gps._lon)!=0) _state=RUNNING;
}

void Cansat::judgeGoal(){
  long dLat = _dest_Lat - gps._lat;
  long dLon = _dest_Lon - gps._lon;
  if(abs(dLat)<=GOAL_THRE && abs(dLog)<=GOAL_THRE){
    _state=GOAL;
  }

}

void Cansat::judgeIdling2Running(){

}

void Cansat::judgeStucking2Running(){

}

void Cansat::preparing(){
  rightMotor.stop();
  leftMotor.stop();
  // このループ入った時の時間を保存．
  /* GPS 座標が指定数以上で起動と判断し起動時間を記録 */
  // 数は http://library.jsce.or.jp/jsce/open/00037/1997/562-0141.pdf より 6 に設定 (20160526現在)
  // if (io_cansat -> state_data == PREPARING && io_cansat->gps_data.SatNum >= 6) {
}

void Cansat::flying(){
  // ここも特に光ピコピコさせるだけじゃない？
}
void Cansat::dropping(){
  // このループ入った時の時間を保存．
  // ここも特に光ピコピコさせるだけじゃない？
}
void Cansat::landing(){
  // このループ入った時の時間を保存．
  // ここも特に光ピコピコさせるだけじゃない？
}

void Cansat::running(){
  /** ここは小柳やってね
  */
  // このループ入った時の時間を保存．
  // witchWay2Go();
  // motorControl();
}

void Cansat::idling(){
  // 何もしないらしい
}

void Cansat::stucking(){
  int count=0;
  while(_state==STUCKING){
    if(count>170){
      rightMotor.goStraight(255);
      leftMotor.goStraight(200);
    }else{
      rightMotor.goStraight(200);
      leftMotor.goStraight(255);
    }
  }
}

void Cansat::goal(){
    rightMotor.stop();
    leftMotor.stop();
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
