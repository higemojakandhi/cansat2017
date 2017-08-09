/**
* @file openlog.cpp
* @author Kandai Watanabe
* @date Created: 20170506
*/
#include "openlog.h"

OpenLog::OpenLog(int pinOpenLogReset){
  _serial = NULL;
  _pinOpenLogReset = pinOpenLogReset;
  pinMode(_pinOpenLogReset, OUTPUT);
}

OpenLog::~OpenLog(){
  _serial=NULL;
}

void OpenLog::init(HardwareSerial* serial){
  _serial = serial;
  reset();

  // Creating New File
  int numLog=100;
  sprintf(_logFile, "log%03d.txt", numLog);
  gotoCommandMode();
  createFile(_logFile);
  Serial.println("OpenLog Begin!"); _serial->println("OpenLog Begin!");
  _serial->print("Time[ms], State, Light, numSat, PosAccuracy, alt, Lat, Lon, ");
  _serial->println("accX, accY, accZ, gyroX, gyroY, gyro, Pitch, Roll, Yaw, Deg");

  sprintf(_errorFile, "err%03d.txt", numLog);
  gotoCommandMode();
  createFile(_errorFile);
  Serial.println("Error File Created!"); _serial->println("Error File Created!");
}

void OpenLog::reset(){
  digitalWrite(_pinOpenLogReset, LOW);
  delay(100);
  digitalWrite(_pinOpenLogReset, HIGH);
  delay(3000);
}

void OpenLog::openErrorFile(){
  gotoCommandMode();
  appendFile(_errorFile);
}

void OpenLog::saveErrorOnSD(String error){
  _serial->println(error);
}

void OpenLog::saveDataOnSD(String alldata){
  gotoCommandMode();
  appendFile(_logFile);
  //OpenLog is now waiting for characters and will record them to the new file
  _serial->println(alldata);
}

void OpenLog::createFile(char *fileName) {
  // Create New file
  _serial->print("new ");
  _serial->print(fileName);
  _serial->write(13); //This is \r
  //Wait for OpenLog to return to waiting for a command
  waitUntilReady2ReceiveCommand();

  // Append New File
  _serial->print("append ");
  _serial->print(fileName);
  _serial->write(13); //This is \r
  waitUntilReady2Log();
  //OpenLog is now waiting for characters and will record them to the new file
}

void OpenLog::appendFile(char *fileName){
  _serial->print("append ");
  _serial->print(fileName);
  _serial->write(13); //This is \r
  waitUntilReady2Log();
  //OpenLog is now waiting for characters and will record them to the new file
}

void OpenLog::waitUntilReady2Log(){
  //Wait for OpenLog to respond with '<' to indicate we are ready to log
  int i=0;
  while(1){
    if(_serial->available()){
      if(_serial->read() == '<')  break;
      // Serial.println("not ready to Log");
    }else{
      if(i==200) reset(); Serial.println("OpenLog Reset");
      // Serial.println("not available");
    }
    i++;
  }
}

void OpenLog::waitUntilReady2ReceiveCommand(){
  int i=0;
  //Wait for OpenLog to respond with '>' to indicate we are in command mode
  while(1) {
    if(_serial->available()){
      if(_serial->read() == '>') break;
      //  Serial.println("not ready to Receive Command");
    }else{
      if(i==200) reset(); Serial.println("OpenLog Reset");
      // Serial.println("not available");
    }
    i++;
  }
}

//This function pushes OpenLog into command mode
void OpenLog::gotoCommandMode() {
  //Send three control z to enter OpenLog command mode
  //Works with Arduino v1.0
  // Serial.println("before Command");
  _serial->write(26);
  _serial->write(26);
  _serial->write(26);
  // Serial.println("after Command");
  waitUntilReady2ReceiveCommand();
}
