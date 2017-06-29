
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

#define PREPARING 0   // 準備状態（電源オン→GPS衛星補足までの間）
#define DROPPING 1    // 地上期（運搬→ロケット収納→ロケット発射）
#define FLYING 2      // 降下中
#define LANDING 3     // ジャイロ加速度センサによる着地検知
#define RUNNING 4     // 走行中
#define IDLING 5      // アイドリング
#define STUCKING 6       // スタック中
#define GOAL 7        // ゴール

#endif
