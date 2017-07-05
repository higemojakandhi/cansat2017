
/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define PIN_RIGHT_MOTOR_VREF 3
#define PIN_RIGHT_MOTOR_FIN 4
#define PIN_RIGHT_MOTOR_RIN  5
#define PIN_LEFT_MOTOR_VREF 9
#define PIN_LEFT_MOTOR_FIN 10
#define PIN_LEFT_MOTOR_RIN  11

#define PIN_OPENLOG_RESET 22
#define PIN_LIGHT A0
#define PIN_GPS_RX 19
#define PIN_GPS_TX 18

#define PIN_RELEASING 6


// SEQUENCE
#define PREPARING 0   // 準備状態（電源オン→GPS衛星補足までの間）
#define DROPPING 1    // 地上期（運搬→ロケット収納→ロケット発射）
#define FLYING 2      // 降下中
#define LANDING 3     // ジャイロ加速度センサによる着地検知
#define RUNNING 4     // 走行中
#define IDLING 5      // アイドリング
#define STUCKING 6       // スタック中
#define GOAL 7        // ゴール


// THRESHOLD
#define PRE2FLY_THRE 100              // キャリア格納判定用　（光センサの閾値）
#define FLY2DROP_THRE 100             // 放出判定用　　　　　（光センサの閾値）
#define RELEASING_TIME_THRE 10000     // スタック防止機構 稼働時間の閾値 [ms]

#define LandingTime_thre 180000       // 着地検知の冗長系：時間でシークエンス移行
#define ReleaseTime_thre  15000       // パラ分離時間の閾値 [ms]
#define EvasionTime_thre  10000       ]
#define GoForward_thre    20000       // 防止機構の稼働時間経過 -> この時間 [ms] まっすぐ進む
#define GoalLEDs_thre     20000       // ゴール後のLED点灯時間
#define COUNT_PRE2FLY_LOOP_THRE 30
#define COUNT_FLY2DROP_LOOP_THRE 100

#define GOAL_THRE 5;

#endif
