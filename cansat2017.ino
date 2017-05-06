/**
  @file cansat2017.ino
  @brief CanSat Project 2017
  @author Kandai Watanabe
  @date Created: 20170420
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "motor.h"
#include "openlog.h"
#include "cansat.h"

int count = 0;
Cansat cansat;
// このスコープでglobal objectのcansatを生成
// そうすればsetup()でもloop()でも使用できるので
// Serialの場合はsetupでinitしてあげる．constructorは？ポインターは定義しておいて，NULLを指しておけば大丈夫．intは0とか．
// &addressで渡せば下位のscopeまで使える．例えばSerial
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Begin!");
  cansat.init();
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

    mymotor.goStraight();
    Serial.println(mymotor.getMotorPin());

  */
  cansat.motor->goStraight();
  count += 1;
  Serial.println(count);
  /** state判定

  */

  /** LED点滅
    LED.flash"Sequence名"
  */

  // -------------------------------------------------------------------------
  // sequenceごと終了

  /**
    全て処理が終わったらループの最後にSDにデータの記録
    OpenLog.saveAllData();
  */
  //  cansat.openlog->saveDataOnSD();
}
