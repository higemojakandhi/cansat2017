
/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

// ピン
#define PIN_LED_RED A0
#define PIN_LED_BLUE A1
#define PIN_LED_GREEN A2
#define PIN_LIGHT A15
#define PIN_OPENLOG_RESET 3
#define PIN_LEFT_MOTOR_FIN 9
#define PIN_LEFT_MOTOR_RIN 10
#define PIN_RIGHT_MOTOR_FIN 44
#define PIN_RIGHT_MOTOR_RIN 46
#define PIN_RELEASING 13
#define PIN_INTERRUPT 22
#define PIN_RELEASING_XBEE1 23
#define PIN_RELEASING_XBEE2 25

// シークエンス
#define PREPARING 0   // 準備状態（電源オン→GPS衛星補足までの間）
#define FLYING 1      // 降下中
#define DROPPING 2    // 地上期（運搬→ロケット収納→ロケット発射）
#define LANDING 3     // ジャイロ加速度センサによる着地検知
#define RUNNING 4     // 走行中
#define RELEASING 5   // XBEE 分離
#define STUCKING 6    // スタック中
#define GOAL 7        // ゴール
#define STANDBY 10    // デバッグ用にステート移行しないように停止

// THRESHOLD
// preparing()
#define PRE2FLY_THRE 100              // キャリア格納判定用　（光センサの閾値）
#define COUNT_PRE2FLY_LOOP_THRE 15   // キャリア格納判定用  (閾値以下の値になる連続の回数の閾値
// flying()
#define FLY2DROP_THRE 100             // 放出判定用　　　　　（光センサの閾値）
#define COUNT_FLY2DROP_LOOP_THRE 15  // 放出判定用          (閾値以上の値になる連続の回数の閾値
// dropping()
  // 加速度
#define ACCEL_THRE  1.2               // 加速度の閾値
#define GYRO_THRE   10                // ジャイロの閾値
#define COUNT_DROP2LAND_LOOP_THRE 15 // 着地検知用          (ジャイロ・加速度の連続の回数の閾値
  // 高度
#define ALT_THRE    5                       // 10秒間でGPSの高度が5m変化しないかどうかの閾値
#define COUNT_DROP2LAND_GPS_LOOP_THRE 5     // 着地検知用        (10秒間でGPSの高度が5m変化していないループ回数の閾値)
#define BETWEEN_NOW_AND_PRE_ALT_TIME 240000 // 前回GPSの高度を保存した時刻と今の時刻との差の閾値
  // 冗長系
#define LANDING_TIME_THRE 180000      // 着地検知の冗長系：時間でシークエンス移行
// landing()
#define RELEASING_TIME_THRE 17000     // 分離時間
// running()
#define GOAL_THRE 5     // 5m以内がゴール
// guidance()
#define ANGLE_THRE 20   // 目的地が角度以下なら真っ直ぐ進む
// judgeStucking()
#define STUCKING_JUDGE_TIME_THRE 10000 // スタック検知する間隔

#endif
