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
Cansat cansat = Cansat(int date=100);

/** 初期化関数
*/
void setup() {
  // Serial通信開始
  Serial.begin(9600);
  delay(500);
  Serial.println("Begin!");
  // GPS　と OpenLog Serial通信開始
  SerialGps.begin(9600);
  SerialOpenLog.begin(9600);
  // cansatにSerialを渡す & 初期化
  cansat.init(&SerialGps, &SerialOpenLog, &SerialRadio);
  Serial.println("All Set!");
}

/** ループ関数
*/
void loop() {
  /**　初期化
    出来ればセンサーのキャリブレーション毎回したい．もしくは数分に１回
      if(ever5min()) sensor.calibrate();
  */

  /**　センサー値取得
    ループでは常にGPSはon, デジコンはendbeginで取得, ライトは pre, fly,dropでon, GYROもon, OpenLogも常にon
    MU2はPre, Drop, Land, Goalの時だけ送信
  */
  cansat.getSensorValues();

  /** cansatの状態(State)に応じて処理を変更
  */
    switch (cansat._state) {
      case PREPARING:
        cansat.preparing();
        cansat.isPreparing2Flying();
        // judge
        // light
        break;
      case FLYING:
        cansat.flying();
        cansat.isFlying2dropping();
        break;
      case DROPPING:
        cansat.dropping();
        cansat.isDropping2Landing();
        break;
      case LANDING:
        cansat.landing();
        cansat.isLanding2Running();
        break;
      case RUNNING:
        cansat.dropping();
        cansat..isIdling();
        cansat.isStucking();
        cansat.isGoal();
        break;
      case IDLING:
        cansat.idling();
        cansat.isIdling2Running();
        break;
      case STUCKING:
        cansat.stucking();
        cansat.isStucking2Running();
        break;
      case GOAL:
        cansat.goal();
        break;
      default:
        break;
    }

  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.saveAllData();
}
