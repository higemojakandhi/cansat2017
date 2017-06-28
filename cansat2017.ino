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
  delay(500);         Serial.println("Begin!");

  SerialGps.begin(9600);
  SerialOpenLog.begin(9600);

  cansat.init(&SerialGps, &SerialOpenLog, &SerialRadio);

  Serial.println("All Set!");
}

void loop() {
  /**　初期化
    データの格納庫の初期化
      openlog.deleteTempData();
    送信コマンドデータの格納庫の初期化
      serialcommand.deleteTempData();
    出来ればセンサーのキャリブレーション毎回したい．もしくは数分に１回
      if(ever5min()) sensor.calibrate();
  */

  /* stateは手動でも変更可能
    state.changeByHand();
  */
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
  if(i==255) i=0;
//  cansat.rightMotor.goStraight(i);
//  cansat.leftMotor.goStraight(i);

  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.saveAllData();
  i++;
}
