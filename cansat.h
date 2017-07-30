/**
* @file cansat.h
* @author Kandai Watanabe
* @date Created: 20170423
*/
#ifndef _CANSAT_H_
#define _CANSAT_H_
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "constant.h" //ALL CONSANTS ARE HERE!!! ex) Pin Number
#include "motor.h"
#include "light.h"
#include "gps.h"
#include "nineaxis.h"
#include "openlog.h"
#include "radio.h"

class Cansat {
public:
  // Initialization (Constructor and Destructor)
  Cansat();
  ~Cansat();
  void setSerial(HardwareSerial* serialgps, HardwareSerial* serialopenlog, HardwareSerial* serialradio);

  // Objects
  Motor leftMotor = Motor(PIN_LEFT_MOTOR_FIN, PIN_LEFT_MOTOR_RIN);
  Motor rightMotor = Motor(PIN_RIGHT_MOTOR_FIN, PIN_RIGHT_MOTOR_RIN);
  Light light = Light(PIN_LIGHT);
  // Serial 通信 (Pin番号の指定いらない)
  Gps gps;
  OpenLog openlog = OpenLog(PIN_OPENLOG_RESET);
  Radio radio;
  // I2C 通信 (Pin番号の指定いらない)
  NineAxis nineaxis;

  // Functions
  void preparing();
  void flying();
  void dropping();
  void landing();
  void running();
  void idling();
  void stucking();
  void goal();
  void judgeIdling2Running();
  void judgeStucking2Running();
  void whichWay2Go(float lat, float lon, float deg);

  void judgeIdling();
  void judgeStucking();
  void judgeGoal();

  // State Switcher
  void switchStateTo(byte state);

  // Variables to save
  int _state;
  unsigned long _startPreparingTime;
  unsigned long _startFlyingTime;
  unsigned long _startDroppingTime;
  unsigned long _startLandingTime;
  unsigned long _startRunningTime;

  unsigned long _preGpsPollingTime;
  float _pre20sGpsLat;
  float _pre20sGpsLon;

  float _destLat;
  float _destLon;
  float _distance;

  int _flagLandingTime;

  int _countPreLightLoop;
  int _countFlyLightLoop;
  int _countDrop2LandLoop;

  int _direct;
  int _bodyAngle;
};

#endif
