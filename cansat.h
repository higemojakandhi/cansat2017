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
  void setGoal(float destLat, float destLon);
  void setSerial(HardwareSerial* serial);

  // Objects
  Motor leftMotor = Motor(PIN_LEFT_MOTOR_FIN, PIN_LEFT_MOTOR_RIN);
  Motor rightMotor = Motor(PIN_RIGHT_MOTOR_FIN, PIN_RIGHT_MOTOR_RIN);
  Light light = Light(PIN_LIGHT);
  // Serial 通信 (Pin番号の指定いらない)
  Gps gps;
  OpenLog openlog = OpenLog(PIN_OPENLOG_RESET);
  Radio radio;
  // I2C 通信 (Pin番号の指定いらない)
  NineAxis nineaxis = NineAxis(PIN_INTERRUPT);

  // Functions
  void preparing();
  void flying();
  void dropping();
  void landing();
  void running();
  void releasing();
  void stucking();
  void goal();
  void judgeStucking2Running();
  void whichWay2Go(float lat, float lon, float deg);
  void whichDirection(float deg);

  void judgeStucking();
  void judgeGoal();

  // State Switcher
  void switchStateTo(byte state);

  // Variables to save
  int _state;
  unsigned long _startPreparingTime=0;
  unsigned long _startFlyingTime=0;
  unsigned long _startDroppingTime=0;
  unsigned long _startLandingTime=0;
  unsigned long _startRunningTime=0;

  unsigned long _preGpsPollingTime=0;
  float _pre20sGpsLat=0;
  float _pre20sGpsLon=0;

  float _destLat;
  float _destLon;
  float _distance;

  int _flagLandingTime=0;
  int _flagXBeeReleasingNum=1;

  int _countPreLightLoop=0;
  int _countFlyLightLoop=0;
  int _countDrop2LandLoop=0;
  int _countDrop2LandGPSLoop=0;
  int _preAltSavedTime=0;
  float _preAlt=0;

  HardwareSerial* _serial;
  int _direct;
  int _bodyAngle;
  float _bodyLat;
  float _bodyLon;
};

#endif
