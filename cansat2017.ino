/**
* @file cansat2017.ino
* @brief CanSat Project 2017
* @author Kandai Watanabe
* @date Created: 20170420
* @date Modified: 20170420
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "motor.h"

int MOTOR_PIN = 8;
int FIN_PIN = 40;
int RIN_PIN = 30;

// ここでCanSat 全部初期化したいな
Motor mymotor(MOTOR_PIN, FIN_PIN, RIN_PIN);
void setup() {
  Serial.begin(9600);
  Serial.println("Begin!");
}

void loop() {
  /**　初期化
  * データの格納庫の初期化
  *   openlog.deleteTempData();
  * 送信コマンドデータの格納庫の初期化
  *   serialcommand.deleteTempData();
  * 出来ればセンサーのキャリブレーション毎回したい．もしくは数分に１回
  *   if(ever5min()) sensor.calibrate();
  */

  /* stateは手動でも変更可能
  * state.changeByHand();
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
  * ループでは常にGPSはon, デジコンはendbeginで取得, ライトは pre, fly,dropでon, GYROもon, OpenLogも常にon
  * MU2はPre, Drop, Land, Goalの時だけ送信
  */

  /** やるべきことやる
  *
  mymotor.goStraight();
  Serial.println(mymotor.getMotorPin());
  *
  */

  /** state判定
  *
  */

  /** LED点滅
  * LED.flash"Sequence名"
  */

  // -------------------------------------------------------------------------
  // sequenceごと終了

  /**
  * 全て処理が終わったらループの最後にSDにデータの記録
  * OpenLog.saveAllData();
  */
}
