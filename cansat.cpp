/**
* @file cansat.cpp
* @author Kandai Watanabe
* @date Created: 20170423
*/
#include "cansat.h"

Cansat::Cansat() {
  pinMode(PIN_RELEASING, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_RELEASING_XBEE1, OUTPUT);
  pinMode(PIN_RELEASING_XBEE2, OUTPUT);
}

Cansat::~Cansat() {
}

/**
* @func setGoal(float destlat, float destLon)
* @brief 目的地を設定する
* @detail
*/
void Cansat::setGoal(float destLat, float destLon) {
  _destLat = destLat;
  _destLon = destLon;
}

void Cansat::setSerial(HardwareSerial* serial) {
  _serialOpenLog = serial;
}

void Cansat::preparing() { // State: 0
  // このループ入った時間を保存．
  if (_startPreparingTime == 0) {
    _startPreparingTime = millis();
    // LED は光らせない
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 0);
  }

  // モータは停止
  rightMotor.stop();
  leftMotor.stop();

  Serial.print(F("Start Preparing Time: "));          Serial.print(_startPreparingTime);
  Serial.print(F("   Now: "));                        Serial.println(millis());
  if(DEBUG_OPENLOG){
    _serialOpenLog->print(F("Start Preparing Time: ")); _serialOpenLog->print(_startPreparingTime);
    _serialOpenLog->print(F("   Now: "));               _serialOpenLog->println(millis());
  }
  // Flyingのジャッジ
  if (light._lightValue < PRE2FLY_THRE) {
    _countPreLightLoop++;
    if (_countPreLightLoop > COUNT_PRE2FLY_LOOP_THRE) _state = FLYING;
  } else {
    _countPreLightLoop = 0;
  }
}

void Cansat::flying() { //State: 1
  // このループ入った時間を保存．
  if (_startFlyingTime == 0) {
    _startFlyingTime = millis();
    analogWrite(PIN_LED_BLUE, 255);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 0);
  }

  // モータは停止
  rightMotor.stop();
  leftMotor.stop();

  Serial.print(F("Start Flying Time: "));           Serial.print(_startFlyingTime);
  Serial.print(F("   Now: "));                      Serial.println(millis());
  if(DEBUG_OPENLOG){
    _serialOpenLog->print(F("Start Flying Time: "));  _serialOpenLog->print(_startFlyingTime);
    _serialOpenLog->print(F("   Now: "));             _serialOpenLog->println(millis());
  }

  // Droppingのジャッジ
  if (light._lightValue > FLY2DROP_THRE) {
    _countFlyLightLoop++;
    if (_countFlyLightLoop > COUNT_FLY2DROP_LOOP_THRE) _state = DROPPING;
  } else {
    _countFlyLightLoop = 0;
  }
}

void Cansat::dropping() { //State: 2
  // このループ入った時間を保存．
  if (_startDroppingTime == 0) {
    _startDroppingTime = millis();
    // 光ピコピコ
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 255);
    analogWrite(PIN_LED_RED, 0);
  }

  Serial.print(F("Start Dropping Time: "));     Serial.print(_startDroppingTime);
  Serial.print(F("   Now: "));                  Serial.println(millis());
  if(DEBUG_OPENLOG){
    _serialOpenLog->print(F("Start Dropping Time: "));  _serialOpenLog->print(_startDroppingTime);
    _serialOpenLog->print(F("   Now: "));               _serialOpenLog->print(millis());
  }


  // 加速度とジャイロから着地検知
  if ((pow(nineaxis.ax, 2) + pow(nineaxis.ay, 2) + pow(nineaxis.az, 2)) < ACCEL_THRE ^ 2) { //　加速度の合計が1.2?以}下
    if (fabs(nineaxis.gx) < GYRO_THRE && fabs(nineaxis.gy) < GYRO_THRE && fabs(nineaxis.gz) < GYRO_THRE) {
      _countDrop2LandLoop++;
      if (_countDrop2LandLoop > COUNT_DROP2LAND_LOOP_THRE){
        _state = LANDING;

        Serial.println(F("JudgeLanding: Accel&Gyro"));
        Serial.print(F("millis: "));                              Serial.println(millis());
        if(DEBUG_OPENLOG){
          _serialOpenLog->println(F("JudgeLanding: Accel&Gyro"));
          _serialOpenLog->print(F("millis: "));                   _serialOpenLog->println(millis());
        }
      }
    } else {
      _countDrop2LandLoop = 0;
    }
  }
 //
 // // 高度で着地検知
 // if (_preAlt == 0) {
 //   if (gps._lat <= 1 && gps._lon <= 1) {
 //     _preAlt = gps._alt;                 // これ高度0だったらどうするん
 //     _preAltSavedTime = millis();
 //   }
 // } else {
 //   if (millis() - _preAltSavedTime > BETWEEN_NOW_AND_PRE_ALT_TIME) {
 //     if ((_preAlt<gps._alt) && (_preAlt - gps._alt<ALT_THRE)) {
 //       _state = LANDING;
 //
 //       Serial.println(F("JudgeLanding: GPS Altitude"));
 //       Serial.print(F("PreAltSavedTime: "));                             Serial.print(_preAltSavedTime);
 //       Serial.print(F("   Now: "));                                      Serial.print(millis());
 //       Serial.print(F("   BETWEEN_NOW_AND_PRE_ALT_TIME: "));             Serial.println(BETWEEN_NOW_AND_PRE_ALT_TIME);
 //       if(DEBUG_OPENLOG){
 //         _serialOpenLog->println(F("JudgeLanding: GPS Altitude"));
 //         _serialOpenLog->print(F("PreAltSavedTime: "));                  _serialOpenLog->print(_preAltSavedTime);
 //         _serialOpenLog->print(F("   Now: "));                           _serialOpenLog->print(millis());
 //         _serialOpenLog->print(F("   BETWEEN_NOW_AND_PRE_ALT_TIME: "));  _serialOpenLog->println(BETWEEN_NOW_AND_PRE_ALT_TIME);
 //       }
 //     }
 //     _preAltSavedTime = millis();
 //   }
 // }

//  // 時間で着地検知
//  if (_startDroppingTime != 0) {
//    if (millis() - _startDroppingTime > LANDING_TIME_THRE) {
//      _state = LANDING;
//
//      Serial.print(F("Start Dropping Time: "));     Serial.print(_startDroppingTime);
//      Serial.print(F("   Now: "));                  Serial.print(millis());
//      Serial.print(F("   LANDING_TIME_THRE: "));    Serial.println(LANDING_TIME_THRE);
//      if(DEBUG_OPENLOG){
//        _serialOpenLog->print(F("Start Dropping Time: "));  _serialOpenLog->print(_startDroppingTime);
//        _serialOpenLog->print(F("   Now: "));               _serialOpenLog->print(millis());
//        _serialOpenLog->print(F("   LANDING_TIME_THRE: ")); _serialOpenLog->println(LANDING_TIME_THRE);
//      }
//    }
//  }
}

void Cansat::landing() { //State: 3
  // このループ入った時間を保存．
  if (_startLandingTime == 0) {
    _startLandingTime = millis();
    // 光ピコピコ
    analogWrite(PIN_LED_BLUE, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_RED, 255);
  }

  // Landing検知したらReleasePin焼き切る
  digitalWrite(PIN_RELEASING_XBEE2, HIGH);
  // ある一定時間過ぎたらRunningにする
  if (_startLandingTime != 0) {
    if (millis() - _startLandingTime > RELEASING_TIME_THRE) {
      digitalWrite(PIN_RELEASING_XBEE2, LOW);
      _state = RUNNING;

      Serial.print(F("Start Landing Time: "));              Serial.print(_startLandingTime);
      Serial.print(F("   Now: "));                          Serial.print(millis());
      Serial.print(F("   RELEASING_TIME_THRE: "));          Serial.println(RELEASING_TIME_THRE);
      if(DEBUG_OPENLOG){
        _serialOpenLog->print(F("Start Landing Time: "));     _serialOpenLog->print(_startLandingTime);
        _serialOpenLog->print(F("   Now: "));                 _serialOpenLog->print(millis());
        _serialOpenLog->print(F("   RELEASING_TIME_THRE: ")); _serialOpenLog->println(RELEASING_TIME_THRE);
      }
    }
  }
}

void Cansat::running() { //State: 4
  // 走行中はLED光らせない
  analogWrite(PIN_LED_BLUE, 0);
  analogWrite(PIN_LED_GREEN, 0);
  analogWrite(PIN_LED_RED, 0);

  // GPSが入ってこなかったらとりあえずうごかない
  // GPSの値0なはずだけど，ログ見ると0.000となっていて小数点が不安だったので一応1以下にした
  if (gps._lat < 1 && gps._lon < 1) {
    leftMotor.stop();
    rightMotor.stop();
  } else {
    // 走り始めた時間を保存
    if (_startRunningTime == 0) {
      _startRunningTime = millis();
      sub_goal1_lat = (_destLat-gps._lat)/3 + gps._lat;
      sub_goal1_lon = (_destLon-gps._lon)/3 + gps._lon;
      sub_goal2_lat = (_destLat-gps._lat)*2/3 + gps._lat;
      sub_goal2_lon = (_destLon-gps._lon)*2/3 + gps._lon;
    }

    // Xbee1 を落とすまで．
    if(_running_state==1){
      guidance(gps._lat, gps._lon, nineaxis.deg, sub_goal1_lat, sub_goal1_lon);
      if (fabs(sub_goal1_lat - gps._lat) * 100000 <= GOAL_THRE && fabs(sub_goal1_lon - gps._lon) * 100000 <= GOAL_THRE){
        _state=RELEASING;
      }
    // Xbee2 を落とすまで．
    }else if(_running_state==2){
      guidance(gps._lat, gps._lon, nineaxis.deg, sub_goal2_lat, sub_goal2_lon);
      if (fabs(sub_goal2_lat - gps._lat) * 100000 <= GOAL_THRE && fabs(sub_goal2_lon - gps._lon) * 100000 <= GOAL_THRE){
        _state=RELEASING;
      }
    // ゴールまで
    }else{
      guidance(gps._lat, gps._lon, nineaxis.deg, _destLat, _destLon);
      if (fabs(_destLat - gps._lat) * 100000 <= GOAL_THRE && fabs(_destLon - gps._lon) * 100000 <= GOAL_THRE){
        _state = GOAL;
      }
    }
  }
}

void Cansat::guidance(float lat, float lon, float deg, float goalLat, float goalLon) {
  // Lon=経度=x
  // Lat=緯度=y
  float deltaLon = (goalLon - lon) * 100000;
  float deltaLat = (goalLat - lat) * 100000; // メートルに変換
  _distance = sqrt(pow(deltaLat, 2) + pow(deltaLon, 2));
  // 機体座標に変換
  _bodyLon = deltaLon * cos(deg / 180 * M_PI) + deltaLat * sin(deg / 180 * M_PI); // [x'] =  [cos(th)     sin(th)] [x]
  _bodyLat = -deltaLon * sin(deg / 180 * M_PI) + deltaLat * cos(deg / 180 * M_PI); // [y']   [-sin(th)    cos(th)] [y]

  // 機体座標系でのゴールまでの角度を計算
  if (_bodyLat > 0) {
    _bodyAngle = fabs(atan(_bodyLon / _bodyLat)) * 180 / M_PI;
  } else if (_bodyLat < 0) {
    _bodyAngle = 180 - fabs(atan(_bodyLon / _bodyLat)) * 180 / M_PI;
  } else {
    _bodyAngle = 90;
  }
  // ある角度以内なら真っ直ぐ，それ以外で右は右，左は左．
  if (_bodyAngle < ANGLE_THRE) {
    _direct = 0; //真っ直ぐ
  } else {
    if (_bodyLon >= 0) {
      _direct = 1; //右
    } else {
      _direct = -1; //左
    }
  }

  // モータの駆動
  if (_direct == 0) {
    rightMotor.setSpeedAt(255);
    leftMotor.setSpeedAt(255);
  } else if (_direct == 1) { //右
    rightMotor.setSpeedAt(170 * (1 - _bodyAngle / 180));
    leftMotor.setSpeedAt(255);
  } else if (_direct == -1) { //左
    rightMotor.setSpeedAt(255);
    leftMotor.setSpeedAt(170 * (1 - _bodyAngle / 180));
  }
}

void Cansat::releasing() { //State: 5
  if(_startReleasingTime==0) _startReleasingTime=millis();
  leftMotor.stopSlowly();
  rightMotor.stopSlowly();

  if (_running_state == 1) {
    digitalWrite(PIN_RELEASING_XBEE1, HIGH);
    if (millis() - _startReleasingTime > RELEASING_TIME_THRE) {
      digitalWrite(PIN_RELEASING_XBEE1, LOW);
      _state=RUNNING;
      _running_state=2;
      Serial.print(F("Start Releasing Time: "));              Serial.print(_startReleasingTime);
      Serial.print(F("   Now: "));                          Serial.print(millis());
      Serial.print(F("   RELEASING_TIME_THRE: "));          Serial.println(RELEASING_TIME_THRE);
      if(DEBUG_OPENLOG){
        _serialOpenLog->print(F("Start Releasing Time: "));     _serialOpenLog->print(_startReleasingTime);
        _serialOpenLog->print(F("   Now: "));                 _serialOpenLog->print(millis());
        _serialOpenLog->print(F("   RELEASING_TIME_THRE: ")); _serialOpenLog->println(RELEASING_TIME_THRE);
      }
      _startReleasingTime=0;
    }
  } else if (_running_state == 2) {
    digitalWrite(PIN_RELEASING_XBEE2, HIGH);
    if (millis() - _startReleasingTime > RELEASING_TIME_THRE) {
      digitalWrite(PIN_RELEASING_XBEE2, LOW);
      _state=RUNNING;
      _running_state=3;
      Serial.print(F("Start Releasing Time: "));              Serial.print(_startReleasingTime);
      Serial.print(F("   Now: "));                          Serial.print(millis());
      Serial.print(F("   RELEASING_TIME_THRE: "));          Serial.println(RELEASING_TIME_THRE);
      if(DEBUG_OPENLOG){
        _serialOpenLog->print(F("Start Releasing Time: "));     _serialOpenLog->print(_startReleasingTime);
        _serialOpenLog->print(F("   Now: "));                 _serialOpenLog->print(millis());
        _serialOpenLog->print(F("   RELEASING_TIME_THRE: ")); _serialOpenLog->println(RELEASING_TIME_THRE);
      }
      _startReleasingTime=0;
    }
  }
}

/**
* @func judgeStucking()
* @brief スタック検知 & スタック回避検知
* @detail 5s前のGPS座標を保存し，現時刻と比較.
*         全く変化していない場合はスタックと検知
*         少しでも変化した場合はスタック回避と検知
*/
void Cansat::judgeStucking() {
  // STUCKING_JUDGE_TIME_THRE秒前以上経ったらスタック検知
  if (millis() - _lastGpsTime > STUCKING_JUDGE_TIME_THRE ) {
    // GPS座標が全く変化していない場合はスタックと検知
    if (fabs(_lastGpsLat - gps._lat) * 100000 == 0 && fabs(_lastGpsLon - gps._lon) * 100000 == 0){
      if(_state==RUNNING){
        _state = STUCKING;
      }
    }else{
      if(_state==STUCKING){
        _state = RUNNING;
        _startStuckingTime=0;
      }
    }

    // GPS座標と時間を保存
    _lastGpsLat = gps._lat;
    _lastGpsLon = gps._lon;
    _lastGpsTime = millis();
  }
}

/**
* @func stucking()
* @brief ステートがスタックの場合の処理
* @detail 前進5秒，右バックが5秒を繰り返す (ラジコンでやったらすごいうまくスタック回避できた)
*/
void Cansat::stucking() { //State: 6
  // Stuckした時の時間を保存・記録
  if (_startStuckingTime == 0){
    _startStuckingTime = millis();
    Serial.print(F("Start Stucking Time: ")); Serial.println(_startStuckingTime);
  }

  // 5秒ごとに前進・後進の切り替え
  if((millis()-_startStuckingTime)%5000%2==1){
    rightMotor.stop();
    leftMotor.goBack(255);
  }else{
    rightMotor.setSpeedAt(255);
    leftMotor.setSpeedAt(255);
  }
  // stuckから脱出したかジャッジ
  judgeStucking();
}

/**
* @func goal()
* @brief ステートがゴールの場合の処理
* @detail モータゆっくり停止
*         LEDを点滅させる
*/
void Cansat::goal() { //State: 7
  // モータ停止
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

/**
* @func switchStateTo()
* @brief ステートを手動で変更する
* @detail ステートを受け取り，ASCII文字から48引いて10進数に変換
*/
void Cansat::switchStateTo(byte state) {
  _state = (int) state - 48;
  Serial.print(F("Switch to "));
  Serial.println(_state);
}
