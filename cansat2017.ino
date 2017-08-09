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
// 日付とファイル名は毎回指定しようと思う
// date = 20170728;
// time = 014430;
// numFile = 100;

/** 初期化関数
* 全てのセンサーがしっかりセットアップされるまで無限に待つ
* 成功・失敗のメッセージは必ず吐き出すこと
* error:
* success:
*/
void setup() {
  // Serial通信開始
  Serial.begin(9600); Serial.println("Begin!");
  SerialGps.begin(9600);
  SerialOpenLog.begin(9600);
  SerialRadio.begin(9600);
  analogWrite(PIN_LED_BLUE, 255);
  analogWrite(PIN_LED_GREEN, 255);
  analogWrite(PIN_LED_RED, 255);
  // それぞれに bool setSerialで確認
  // if(!cansat.openlog.setSerial()) while(1)
  // while(!cansat.gps.setSerial()){
  //  SerialOpenLog.println(F("error: GPS not available"))
  //  Serial.println(F("error: GPS not available"));
  // }
  cansat.setSerial(&SerialGps, &SerialOpenLog, &SerialRadio);
  cansat.setGoal(35.742628, 140.011140);
  analogWrite(PIN_LED_BLUE, 0);
  analogWrite(PIN_LED_GREEN, 0);
  analogWrite(PIN_LED_RED, 0);
  // それぞれ初期化
  Serial.println("All Set!");
  delay(1000);
}

/** ループ関数
*/
void loop() {
  cansat.openlog.openErrorFile();
  // センサー値取得
  // それぞれのセンサーにOpenLogを渡し，errorメッセージを記録
  // 位置が取れない場合どうする？ flag渡してgpsが不可ならpeed/degからカルマンフィルタで位置を推定
  cansat.gps.readGpsValue();
  // 9軸が取れない場合はどうする？ flag渡して9軸が不可ならgpsのlat/lon/speed/degから計算
  cansat.nineaxis.readNineAxisValue();

  // 手動でcansatの状態を切り替える．
  if(Serial.available()>0){
    byte inputState = Serial.read();
    Serial.print(F("\n"));
    Serial.print(F("I received: "));   // 受信データを送りかえす
    cansat.switchStateTo(inputState);
  }

  // cansatの状態(State)に応じて処理を変更
  Serial.print("State: "); Serial.println(cansat._state);
    switch (cansat._state) {
      case PREPARING: // 0
        cansat.light.readLightValue();
        cansat.preparing();
        break;
      case FLYING: // 1
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
        break;
      case STUCKING: // 6
        cansat.stucking();
        break;
      case GOAL: // 7
        cansat.goal();
        break;
      case DEBUG: //10
        cansat.rightMotor.stop();
        cansat.leftMotor.stop();
        digitalWrite(PIN_RELEASING, LOW);
        digitalWrite(PIN_RELEASING_XBEE2, LOW);
      default:
        break;
    }

  // 送信用のデータ作成
  String alldata = "";
  alldata += String(millis()) + ", ";
  alldata += String(cansat._state) + ", ";
  alldata += String(cansat.light._lightValue) + ", ";
  alldata += String(cansat.gps._satNum) + ", ";
  alldata += String(cansat.gps._posAccuracy) + ", ";
  alldata += String(cansat.gps._alt) + ", ";
  alldata += String(cansat.gps._lat*1000000) + ", ";
  alldata += String(cansat.gps._lon*1000000) + ", ";
  alldata += String(cansat.nineaxis.ax) + ", ";
  alldata += String(cansat.nineaxis.ay) + ", ";
  alldata += String(cansat.nineaxis.az) + ", ";
  alldata += String(cansat.nineaxis.gx) + ", ";
  alldata += String(cansat.nineaxis.gy) + ", ";
  alldata += String(cansat.nineaxis.gz) + ", ";
  alldata += String(cansat.nineaxis.pitch) + ", ";
  alldata += String(cansat.nineaxis.roll) + ", ";
  alldata += String(cansat.nineaxis.yaw) + ", ";
  alldata += String(cansat.nineaxis.deg) + ", ";

  Serial.print("Time[ms], State, Light, numSat, PosAccuracy, alt, Lat, Lon, ");
  Serial.println("accX, accY, accZ, gyroX, gyroY, gyro, Pitch, Roll, Yaw, Deg");
  Serial.println(alldata);
  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.openlog.saveDataOnSD(alldata);
  // Xbeeに同じデータを送信
 if(cansat._state!=FLYING) cansat.radio.send(alldata);
}
