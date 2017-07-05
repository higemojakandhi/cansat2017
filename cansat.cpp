/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat(){
  _state=0;
  _startPreparingTime=0;
  _startFlyingTime=0;
  _startDroppingTime=0;
  _startLandingTime=0;
  _startRunningTime=0;
  _countPreLightLoop=0;
  _countFlyLightLoop=0;
}

Cansat::~Cansat(){
}

void Cansat::init(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio){
  gps.setSerial(serialgps);
  openlog.init(serialopenlog);
//  radio.setSerial(serialradio);
}

void Cansat::preparing(){
  // このループ入った時の時間を保存．
  if(_startPreparingTime==0) _startPreparingTime = millis();
  // モータは停止
  rightMotor.stop();
  leftMotor.stop();

  // Flyingのジャッジ
  if(light._lightValue < PRE2FLY_THRE) {
    _countPreLightLoop++;
    if (_countPreLightLoop > COUNT_PRE2FLY_LOOP_THRE) _state=FLYING;
  }else{
    _countPreLightLoop=0;
  }
}

void Cansat::flying(){
  // このループ入った時の時間を保存．
  if(_startFlyingTime==0) _startFlyingTime = millis();
  // 光ピコピコ

  // Droppingのジャッジ
  if(light._lightValue > FLY2DROP_THRE){
    _countFlyLightLoop++;
    if(_countFlyLightLoop > COUNT_FLY2DROP_LOOP_THRE) _state=DROPPING;
  }else{
    _countFlyLightLoop=0;
  }
}

void Cansat::dropping(){
  // このループ入った時の時間を保存．
  if(_startDroppingTime==0) _startDroppingTime = millis();
  // 光ピコピコ
/**************************************************************************
  // Landingのジャッジ
  for(int i=0; i<3; i++){
    // 角度，各加速度，加速度がある一定値以下になるのが一定回数以上続けばflag=1;
  }
  // 冗長系である一定時間過ぎたらflagLandingTime=1 -> LANDINGに
  if(_startDroppingTime!=0){
    unsigned long currentTime = millis();
    if(currentTime-_startDroppingTime > LANDING_TIME_THRE) _flagLandingTime = 1;
  }

  // Landing切り替え
  if(_flagLandingTime==1) _state=LANDING;
**************************************************************************/
}

void Cansat::landing(){
  // このループ入った時の時間を保存．
  if(_startLandingTime==0) _startLandingTime = millis();
  // 光ピコピコ

  // Landing検知したらReleasePin焼き切る
  digitalWrite(PIN_RELEASING, HIGH);
  // ある一定時間過ぎたらRunningにする
  if(_startLandingTime!=0){
    unsigned long currentTime = millis();
    if (currentTime - _startLandingTime > RELEASING_TIME_THRE){
      digitalWrite(PIN_RELEASING, LOW);
      _state=RUNNING;
    }
  }
}

void Cansat::running(){
  // このループ入った時の時間を保存
  if(_startRunningTime==0) _startRunningTime = millis();
  int direction=0;
  direction = whichWay2Go(gps._lat, gps._lon, nineaxis._deg);
  /** ここは小柳やってね
  */
  // motorControl();

  // judgeIdling();
  // judgeStucking();
  judgeGoal();
}

int Cansat::whichWay2Go(float lat, float lon, float deg){
  float deltaLat = (_destLat-lat)*0.000001;
  float deltaLon = (_destLat-lat)*0.000001;
  float distance = sqrt(pow(deltaLat,2)+pow(deltaLon,2));
  /*************************************************************************
  *************************************************************************/
  int direction=int(distance);
  return direction;
}

void Cansat::judgeIdling(){
}

void Cansat::judgeStucking(){
  /* スタック検知用に5s前のGPS座標を保存し，現時刻と比較 */
  unsigned long currentGpsPollingTime = millis();
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
  long dLat = _destLat - gps._lat;
  long dLon = _destLon - gps._lon;
  if(abs(dLat)<=GOAL_THRE && abs(dLon)<=GOAL_THRE){
    _state=GOAL;
  }
}

void Cansat::idling(){
  // 何もしないらしい
  judgeIdling2Running();
}

void Cansat::stucking(){
  int count=0;
  // これダメだwww
  // 無限ループに陥る
  while(_state==STUCKING){
    if(count>170){
      rightMotor.goStraight(255);
      leftMotor.goStraight(200);
    }else{
      rightMotor.goStraight(200);
      leftMotor.goStraight(255);
    }
  }
  judgeStucking2Running();
}

void Cansat::judgeIdling2Running(){
}

void Cansat::judgeStucking2Running(){
}

void Cansat::goal(){
    // stop
    rightMotor.stop();
    leftMotor.stop();
    // LED チカチカ
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

void Cansat::switchStateTo(byte state){
  _state = (int) state;
  Serial.print(F("Switch to "));
  Serial.println(_state);
}
