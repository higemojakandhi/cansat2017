
/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define PIN_INTERRUPT 2
#define PIN_RIGHT_MOTOR_FIN 3
#define PIN_RIGHT_MOTOR_RIN 4
#define PIN_LEFT_MOTOR_FIN 9
#define PIN_LEFT_MOTOR_RIN 10

#define PIN_OPENLOG_RESET 22
#define PIN_LIGHT A0
#define PIN_LED_BLUE A1
#define PIN_LED_GREEN A2
#define PIN_LED_RED A3

#define PIN_GPS_RX 19
#define PIN_GPS_TX 18

#define PIN_RELEASING 13
#define PIN_RELEASING_XBEE1 23
#define PIN_RELEASING_XBEE2 25


// SEQUENCE
#define PREPARING 0   // 準備状態（電源オン→GPS衛星補足までの間）
#define FLYING 1      // 降下中
#define DROPPING 2    // 地上期（運搬→ロケット収納→ロケット発射）
#define LANDING 3     // ジャイロ加速度センサによる着地検知
#define RUNNING 4     // 走行中
#define IDLING 5      // アイドリング
#define STUCKING 6    // スタック中
#define GOAL 7        // ゴール
#define DEBUG 10      // デバッグ用にステート移行しないように停止


// THRESHOLD
#define PRE2FLY_THRE 100              // キャリア格納判定用　（光センサの閾値）
#define FLY2DROP_THRE 100             // 放出判定用　　　　　（光センサの閾値）
#define LANDING_TIME_THRE 180000      // 着地検知の冗長系：時間でシークエンス移行
#define RELEASING_TIME_THRE 15000     // 分離時間

#define COUNT_PRE2FLY_LOOP_THRE 100   // キャリア格納判定用  (閾値以下の値になる連続の回数の閾値
#define COUNT_FLY2DROP_LOOP_THRE 100  // 放出判定用          (閾値以上の値になる連続の回数の閾値
#define COUNT_DROP2LAND_LOOP_THRE 200 // 着地検知用          (ジャイロ・加速度の連続の回数の閾値
#define XBEE_DROP_THRE 10000          // Xbee分離時間

#define GOAL_THRE 5     // 5m以内がゴール

#define ANGLE_THRE 20   // 目的地が角度以下なら真っ直ぐ進む

#define ACCELZ_THRE 1   z方向の加速度の閾値
#define GYROX_THRE 10   x方向のジャイロの閾値
#define GYROY_THRE 10   y方向のジャイロの閾値
#define LANDING_TIME_THRE 180000

#endif
