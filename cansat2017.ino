/**
  @file cansat2017.ino
  @brief CanSat Project 2017
  @author Kandai Watanabe
  @date Created: 20170420
*/
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include <HardwareSerial.h>
#include "constant.h" //ALL CONSANTS ARE HERE!!! ex) Pin Number
#include "cansat.h"
HardwareSerial & SerialGps = Serial1;// Change the name of Serial from Serial1 -> SerialGps
HardwareSerial & SerialOpenLog = Serial2; // Change the name of Serial from Serial2 -> SerialOpenlog
HardwareSerial & SerialRadio = Serial3; // Change the name of Serial from Serial3 -> SerialRadio

// cansatオブジェクト生成
Cansat cansat;

/** 初期化関数
*/
void setup() {
  // Serial通信開始
  Serial.begin(9600); delay(500); Serial.println("Begin!");
  SerialGps.begin(9600);
  SerialOpenLog.begin(9600);
  SerialRadio.begin(9600);
  // cansatにSerialを渡す & 初期化
  cansat.setSerial(&SerialGps, &SerialOpenLog, &SerialRadio);
  Serial.println("All Set!");
}

/** ループ関数
*/
void loop() {
  // センサーキャリブレーション

  // センサー値取得
  /**　
    GPS, 9軸は毎ループ
    MU2はPre, Drop, Land, Goalの時だけ送信
    光センサはPre, Flyingのみ．
  */
  cansat.gps.readGpsValue();
  cansat.nineaxis.readNineAxisValue();

  // 手動でcansatの状態を切り替える．
  if(Serial.available()>0){
    byte inputState = Serial.read();
    Serial.print(F("\n"));
    Serial.print(F("I received: "));   // 受信データを送りかえす
    cansat.switchStateTo(inputState);
  }

  /** cansatの状態(State)に応じて処理を変更
  */
  Serial.print("State: "); Serial.println(cansat._state);
    switch (cansat._state) {
      case PREPARING: // 0
        cansat.light.readLightValue();
        cansat.preparing();
        break;
      case FLYING: // 1
        Serial.print("State: now at FLYING: "); Serial.println(cansat._state);
        cansat.light.readLightValue();
        cansat.flying();
        break;
      case DROPPING: // 2
        cansat.dropping();
        break;
      case LANDING: // 3
        cansat.landing();
        break;
      case RUNNING: // 4
        cansat.running();
        break;
      case IDLING: // 5
        cansat.idling();
        // cansat.leftMotor.setSpeedAt(250);
        // cansat.rightMotor.setSpeedAt(250);
        break;
      case STUCKING: // 6
        cansat.stucking();
        break;
      case GOAL: // 7
        cansat.goal();
        break;
      default:
        break;
    }
  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.saveAllData();
  if(cansat._state!=FLYING) cansat.send2Xbee();
}
