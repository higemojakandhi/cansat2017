
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
#define STUCKING 6       // スタック中
#define GOAL 7        // 
#define DEBUG 10


// THRESHOLD
#define PRE2FLY_THRE 100              // キャリア格納判定用　（光センサの閾値）
#define FLY2DROP_THRE 100             // 放出判定用　　　　　（光センサの閾値）
#define RELEASING_TIME_THRE 15000     // スタック防止機構 稼働時間の閾値 [ms]
#define LANDING_TIME_THRE 180000       // 着地検知の冗長系：時間でシークエンス移行

#define ReleaseTime_thre  15000       // パラ分離時間の閾値 [ms]
#define EvasionTime_thre  10000
#define GoForward_thre    20000       // 防止機構の稼働時間経過 -> この時間 [ms] まっすぐ進む
#define GoalLEDs_thre     20000       // ゴール後のLED点灯時間
#define COUNT_PRE2FLY_LOOP_THRE 100
#define COUNT_FLY2DROP_LOOP_THRE 100
#define COUNT_DROP2LAND_LOOP_THRE 200
#define XBEE_DROP_THRE 10000

#define GOAL_THRE 5

#define ANGLE_THRE 20

#define ACCELZ_THRE 1
#define GYROX_THRE 10
#define GYROY_THRE 10
#define LANDING_TIME_THRE 180000

#endif
