/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat(){
  _state=0;
  pinMode(PIN_RELEASING, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_RELEASING_XBEE1, OUTPUT);
  pinMode(PIN_RELEASING_XBEE2, OUTPUT);
}

Cansat::~Cansat(){
}
/**
* @func setGoal(float destlat, float destLon)
* @brief 目的地を設定する
* @detail
*/
void Cansat::setGoal(float destLat, float destLon){
  _destLat = destLat;
  _destLon = destLon;
}

void Cansat::setSerial(HardwareSerial* serial){
  _serial = serial;
}

void Cansat::preparing(){
  // このループ入った時の時間を保存．
  if(_startPreparingTime==0){
    _startPreparingTime = millis();
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 0);
  }

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

void Cansat::flying(){ //1
  // このループ入った時の時間を保存．
  if(_startFlyingTime==0){
    _startFlyingTime = millis();
    analogWrite(PIN_LED_BLUE, 255);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 0);
  }

  // モータは停止
  rightMotor.stop();
  leftMotor.stop();

  // Droppingのジャッジ
  if(light._lightValue > FLY2DROP_THRE){
    _countFlyLightLoop++;
    if(_countFlyLightLoop > COUNT_FLY2DROP_LOOP_THRE) _state=DROPPING;
  }else{
    _countFlyLightLoop=0;
  }
}

void Cansat::dropping(){ //2
  // このループ入った時の時間を保存．
  if(_startDroppingTime==0){
    _startDroppingTime = millis();
    // 光ピコピコ
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 255);
    analogWrite(PIN_LED_RED, 0);
  }

 // 加速度とジャイロから着地検知
 if((pow(nineaxis.ax,2)+pow(nineaxis.ay,2)+pow(nineaxis.az,2))<ACCEL_THRE^2){ //　加速度の合計が1.2?以}下
   if(fabs(nineaxis.gx)<GYRO_THRE && fabs(nineaxis.gy)<GYRO_THRE && fabs(nineaxis.gz)<GYRO_THRE){
     _countDrop2LandLoop++;
     if(_countDrop2LandLoop > COUNT_DROP2LAND_LOOP_THRE) Serial.println("AccelGyro"); _state=LANDING;
   }else{
     _countDrop2LandLoop=0;
   }
 }

 // 高度で着地検知
 if(_preAlt==0){
   _preAlt=gps._alt;
   _preAltSavedTime=millis();
 }else{
   if(millis()-_preAltSavedTime > BETWEEN_NOW_AND_PRE_ALT_TIME){
     if(_preAlt-gps._alt < ALT_THRE){
       _state=LANDING;
     }
     _preAltSavedTime=millis();
   }
 }

  // 時間で着地検知
  if(_startDroppingTime!=0){
//    Serial.print("millis"); Serial.println(millis());
//    Serial.print("Drop time"); Serial.println(_startDroppingTime);
//    Serial.print("Diff"); Serial.println(millis()-_startDroppingTime);
//    Serial.print("LANDING_TIME_THRE"); Serial.println(LANDING_TIME_THRE);
    if(millis()-_startDroppingTime > LANDING_TIME_THRE*2){
      _state = LANDING;
    }
  }
}

void Cansat::landing(){ //3
  // このループ入った時の時間を保存．
  if(_startLandingTime==0){
    _startLandingTime = millis();
    // 光ピコピコ
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 255);
  }

  // Landing検知したらReleasePin焼き切る
  digitalWrite(PIN_RELEASING_XBEE2, HIGH);
  // ある一定時間過ぎたらRunningにする
  if(_startLandingTime!=0){
    if (millis()-_startLandingTime > RELEASING_TIME_THRE){
      digitalWrite(PIN_RELEASING_XBEE2, LOW);
      _state = RUNNING;
      delay(1000);
    }
  }
}

void Cansat::running(){ //4
  // このループ入った時の時間を保存
  if(_startRunningTime==0){
    _startRunningTime = millis();
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 0);
  }

  // GPSが入ってこなかったらとりあえずうごかない // 0なはずだけど，一応1以下にした
  if(gps._lat<=1 && gps._lon<=1){
  // if(_state!=RUNNING){
    leftMotor.stop();
    rightMotor.stop();
  }else{
    // 10秒経ったらXbeeおとす
    if(millis()-_startRunningTime>XBEE_DROP_THRE && _flagXBeeReleasingTime==0){
//    if(_state!=RUNNING){
      leftMotor.stopSlowly();
      rightMotor.stopSlowly();
      digitalWrite(PIN_RELEASING_XBEE1, HIGH);
      if(millis()-_startRunningTime > (XBEE_DROP_THRE+RELEASING_TIME_THRE)){
        digitalWrite(PIN_RELEASING_XBEE1, LOW);
        _flagXBeeReleasingTime=1;
      }
//      delay(RELEASING_TIME_THRE);
//      digitalWrite(PIN_RELEASING_XBEE1, LOW);
//      _flagXBeeReleasingTime=1;
//    }else if(millis()-_startRunningTime>XBEE_DROP_THRE*2 && _flagXBeeReleasingTime==1){
//      leftMotor.stopSlowly();
//      rightMotor.stopSlowly();
//      digitalWrite(PIN_RELEASING_XBEE2, HIGH);
//      if(millis()-_startRunningTime > (XBEE_DROP_THRE*2+RELEASING_TIME_THRE)){
//        digitalWrite(PIN_RELEASING_XBEE2, LOW);
//        _flagXBeeReleasingTime=2;
//      }
    }else{
      // 通常運転
      whichWay2Go(gps._lat, gps._lon, nineaxis.deg);
      // タイヤ動かす．
      if(_direct==0){
        rightMotor.setSpeedAt(255);
        leftMotor.setSpeedAt(255);
      }else if(_direct==1){ //右
        rightMotor.setSpeedAt(170*(1-_bodyAngle/180));
        leftMotor.setSpeedAt(255);
      }else if(_direct==-1){ //左
        rightMotor.setSpeedAt(255);
        leftMotor.setSpeedAt(170*(1-_bodyAngle/180));
      }
    }
  }
   judgeGoal() ;
}

void Cansat::whichDirection(float deg){
  if(fabs(deg)<20){
    _direct=0;
  }else if(deg>=0){
    _direct=1;
  }else{
    _direct=-1;
  }
}

void Cansat::whichWay2Go(float lat, float lon, float deg){
  // Lon=経度=x
  // Lat=緯度=y
  float deltaLon = (_destLon-lon)*100000;
  float deltaLat = (_destLat-lat)*100000; // メートルに変換
  _distance = sqrt(pow(deltaLat,2)+pow(deltaLon,2));
  // 機体座標に変換
  _bodyLon = deltaLon*cos(deg/180*M_PI)+deltaLat*sin(deg/180*M_PI); // [x'] =  [cos(th)     sin(th)] [x]
  _bodyLat = -deltaLon*sin(deg/180*M_PI)+deltaLat*cos(deg/180*M_PI); // [y']   [-sin(th)    cos(th)] [y]

  // 機体座標系でのゴールまでの角度を計算
  if(_bodyLat>0){
    _bodyAngle = fabs(atan(_bodyLon/_bodyLat))*180/M_PI;
  }else if(_bodyLat<0){
    _bodyAngle = 180-fabs(atan(_bodyLon/_bodyLat))*180/M_PI;
  }else{
    _bodyAngle=90;
  }
  // ある角度以内なら真っ直ぐ，それ以外で右は右，左は左．
  if(_bodyAngle<ANGLE_THRE){
    _direct=0; //真っ直ぐ
  }else{
    if(_bodyLon>=0){
      _direct=1; //右
    }else{
      _direct=-1; //左
    }
  }
}

void Cansat::judgeStucking(){
  /* スタック検知用に5s前のGPS座標を保存し，現時刻と比較 */
  if(millis()-_preGpsPollingTime > STUCKING_JUGDE_TIME_THRE ){
    _pre20sGpsLat = gps._lat;
    _pre20sGpsLon = gps._lon;
    _preGpsPollingTime = millis();
  }
  /* RUNNING から STUCK に陥る時の判断 */ 
  if(fabs(_pre20sGpsLat-gps._lat)*100000==0 && fabs(_pre20sGpsLon-gps._lon)*100000==0) _state=STUCKING;
}

void Cansat::judgeGoal(){
  // GOAL_THRE以内ならゴール
  if(fabs(_destLat - gps._lat)*100000<=GOAL_THRE && fabs(_destLon - gps._lon)*100000<=GOAL_THRE) _state=GOAL;

  // 冗長系．時間で検知
  if(millis()-_startRunningTime>GOAL_TIME_THRE) _state = GOAL;
}

void Cansat::stucking(){
  while(_state==STUCKING){
    rightMotor.goBack(255);
    leftMotor.setSpeedAt(255);
    delay(300);
    rightMotor.setSpeedAt(255);
    leftMotor.goBack(255);
    delay(300);
    judgeStucking2Running();
  }
}

void Cansat::judgeStucking2Running(){
  if(millis()-_preGpsPollingTime > STUCKING_JUGDE_TIME_THRE ){
    _pre20sGpsLat = gps._lat;
    _pre20sGpsLon = gps._lon;
    _preGpsPollingTime = millis();
  }
  /* STUCK から RUNNING への判断 */
  if(fabs(_pre20sGpsLat-gps._lat)*100000!=0 || fabs(_pre20sGpsLon-gps._lon)*100000!=0) _state=RUNNING;
}

void Cansat::goal(){
    // stop
    rightMotor.stopSlowly();
    leftMotor.stopSlowly();
    // LED チカチカ
    analogWrite(PIN_LED_BLUE, 255); delay(100);
    analogWrite(PIN_LED_GREEN, 255); delay(100);
    analogWrite(PIN_LED_RED, 255); delay(100);
    
    analogWrite(PIN_LED_BLUE, 0); delay(100);
    analogWrite(PIN_LED_GREEN, 0); delay(100);
    analogWrite(PIN_LED_RED, 0); delay(100);
}

void Cansat::switchStateTo(byte state){
  _state = (int) state - 48;
  Serial.print(F("Switch to "));
  Serial.println(_state);
}
