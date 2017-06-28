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

int date = 100;
Cansat cansat = Cansat(date);
int i=0;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Begin!");

  SerialGps.begin(9600);
  SerialOpenLog.begin(9600);

  cansat.init(&SerialGps, &SerialOpenLog, &SerialRadio);
  Serial.println("All Set!");
}

void loop() {
  /**　初期化
    出来ればセンサーのキャリブレーション毎回したい．もしくは数分に１回
      if(ever5min()) sensor.calibrate();
  */

  /** センサーの値を取得
  */
  cansat.getSensorValues();

  /** cansatの状態(State)に応じて処理を変更
  */
    switch (cansat._state) {
      case PREPARING:
        cansat.preparing();
        break;
      case FLYING:
        cansat.flying();
        break;
      case DROPPING:
        cansat.dropping();
        break;
      case LANDING:
        cansat.landing();
        break;
      case RUNNING:
        cansat.dropping();
        break;
      case IDLING:
        cansat.idling();
        break;
      case STUCK:
        cansat.stuck();
        break;
      case GOAL:
        cansat.goal();
        break;
      default:
        break;
    }

  // -----------------------------ここからstateごとの処理-------------------------
  /** states
    if(cansat.isState("preparing"))
    else if (cansat.isState("flying"))
    else if (cansat.isState("dropping"))
    else if (cansat.isState("landing"))
    else if (cansat.isState("running"))
    else if (cansat.isState("idling"))
    else if (cansat.isState("stuck"))
    else if (cansat.isState("gaol"))
    else
    end
  */

  /**　センサー値取得
    ループでは常にGPSはon, デジコンはendbeginで取得, ライトは pre, fly,dropでon, GYROもon, OpenLogも常にon
    MU2はPre, Drop, Land, Goalの時だけ送信
  */

  /** やるべきことやる
  */

//  cansat.light.readLightValue();
//  Serial.print("Light Value: "); Serial.println(cansat.light.getLightValue());
//
//  cansat.gps.readGpsValue();
//  cansat.gps.showGpsValue();
  /** state判定
  */

  /** LED点滅
    LED.flash"Sequence名"
  */

  // -------------------------------------------------------------------------
  // sequenceごと終了

  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.saveAllData();
  i++;
}
