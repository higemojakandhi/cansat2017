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
#include "constant.h" //全ての定数はここ
#include "cansat.h"
HardwareSerial & SerialGps = Serial1;// Change the name of Serial from Serial1 -> SerialGps
HardwareSerial & SerialOpenLog = Serial2; // Change the name of Serial from Serial2 -> SerialOpenlog
HardwareSerial & SerialRadio = Serial3; // Change the name of Serial from Serial3 -> SerialRadio

// cansatオブジェクト生成
Cansat cansat;
String dataHeader = "Time[ms], Time, State, Light, numSat, PosAccuracy, alt, Lat, Lon, accX, accY, accZ, gyroX, gyroY, gyro, Pitch, Roll, Yaw, Deg";


// ------------------------------------------------------------- SETUP ----------------------------------------------------------------------//
void setup() {
  // Serial通信開始
  Serial.begin(9600); Serial.println(F("Begin!"));
  SerialGps.begin(9600);
  SerialRadio.begin(9600);
  SerialOpenLog.begin(9600);    // より早い読み取りをするには2400, 4800, 9600, 19200, 38400, 57600, and 115200
  // Serial 渡す
  cansat.gps.setSerial(&SerialGps);
  cansat.radio.setSerial(&SerialRadio);
  cansat.openlog.setSerial(&SerialOpenLog);

  // OpenLogに保存するヘッダー渡す
  cansat.openlog.setHeader(&dataHeader);
  // ゴール設定
  cansat.setGoal(35.742628, 140.011140);

  // openlog, 9軸初期化
  cansat.openlog.init();
  analogWrite(PIN_LED_BLUE, 255);
  analogWrite(PIN_LED_GREEN, 255);
  analogWrite(PIN_LED_RED, 255);
  // 特に9軸はキャリブレーションを行う．
  // 3色のLEDが光っている場合は地面に水平に置いて静止 (ジャイロと加速度のキャリブレーション）
  // 2色のLEDが光っている場合は持ってぐるぐる回す     (地磁気のキャリブレーション）
  cansat.nineaxis.init();
  // 終わると光が消える．
  analogWrite(PIN_LED_BLUE, 0);
  analogWrite(PIN_LED_GREEN, 0);
  analogWrite(PIN_LED_RED, 0);

  // それぞれ初期化
  Serial.println(F("All Set!"));
}


// ------------------------------------------------------------- LOOP ----------------------------------------------------------------------//
void loop() {
  cansat.openlog.openErrorFile();
  // それぞれのセンサーにOpenLogを渡し，errorメッセージを記録

  // 位置が取れない場合どうする？ -> 位置推定出来るほど正確なセンサーとモータではないので諦める．
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
  Serial.print(F("State: ")); Serial.println(cansat._state);
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
  String alldata = String(cansat.gps._hour) + String(cansat.gps._minute) + String(cansat.gps._second) + ", "
                 + String(millis()) + ", "
                 + String(cansat._state) + ", "
                 + String(cansat.light._lightValue) + ", "
                 + String(cansat.gps._satNum) + ", "
                 + String(cansat.gps._posAccuracy) + ", "
                 + String(cansat.gps._alt) + ", "
                 + String(cansat.gps._lat*1000000) + ", "
                 + String(cansat.gps._lon*1000000) + ", "
                 + String(cansat.nineaxis.ax) + ", "
                 + String(cansat.nineaxis.ay) + ", "
                 + String(cansat.nineaxis.az) + ", "
                 + String(cansat.nineaxis.gx) + ", "
                 + String(cansat.nineaxis.gy) + ", "
                 + String(cansat.nineaxis.gz) + ", "
                 + String(cansat.nineaxis.pitch) + ", "
                 + String(cansat.nineaxis.roll) + ", "
                 + String(cansat.nineaxis.yaw) + ", "
                 + String(cansat.nineaxis.deg) + ", ";

  Serial.println(alldata);
  // 全て処理が終わったらループの最後にSDにデータの記録
  cansat.openlog.saveDataOnSD(alldata);
  // Xbeeに同じデータを送信
 if(cansat._state!=FLYING) cansat.radio.send(alldata);
}
