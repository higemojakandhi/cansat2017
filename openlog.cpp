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

void OpenLog::setHeader(String* header){
  _header = header;
}
void OpenLog::setSerial(HardwareSerial* serial){
  _serial = serial;
}
void OpenLog::init(){
  reset();

  // Creating New File
  int numLog=1;
  sprintf(_logFile, "log%03d.txt", numLog);
  while(isExist(_logFile)){
    numLog++;
    sprintf(_logFile, "log%03d.txt", numLog);
  }
  gotoCommandMode();
  createFile(_logFile);
  Serial.println("OpenLog Begin!"); _serial->println("OpenLog Begin!");
  _serial->println(*_header);

  if(DEBUG_OPENLOG){
    sprintf(_errorFile, "err%03d.txt", numLog);
    gotoCommandMode();
    createFile(_errorFile);
    Serial.println("Error File Created!"); _serial->println("Error File Created!");
  }
}

void OpenLog::reset(){
  digitalWrite(_pinOpenLogReset, LOW);
  delay(100);
  digitalWrite(_pinOpenLogReset, HIGH);
  delay(3000);
}

void OpenLog::openErrorFile(){
  if(DEBUG_OPENLOG){
    gotoCommandMode();
    appendFile(_errorFile);
  }
}

void OpenLog::saveErrorOnSD(String error){
  if(DEBUG_OPENLOG){
    _serial->println(error);
    delay(20);
  }
}

void OpenLog::saveDataOnSD(String alldata){
  if(DEBUG_OPENLOG){
    gotoCommandMode();
    appendFile(_logFile);
    //OpenLog is now waiting for characters and will record them to the new file
  }
  _serial->println(alldata);
  delay(200);
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
      _connected=true;
    }else{
      if(i==200) reset(); Serial.println(F("OpenLog Reset"));
    }
    i++;
  }
}

void OpenLog::waitUntilReady2ReceiveCommand(){
  //Wait for OpenLog to respond with '>' to indicate we are in command mode
  int i=0;
  while(1) {
    if(_serial->available()){
      if(_serial->read() == '>') break;
      _connected=true;
    }else{
      if(i==200) reset(); Serial.println(F("OpenLog Reset"));
    }
    i++;
  }
}

//This function pushes OpenLog into command mode
void OpenLog::gotoCommandMode() {
  //Send three control z to enter OpenLog command mode
  //Works with Arduino v1.0
  _serial->write(26);
  _serial->write(26);
  _serial->write(26);
  waitUntilReady2ReceiveCommand();
}

bool OpenLog::isExist(char *fileName){
  _serial->print("size ");
  _serial->print(fileName);
  _serial->write(13);

  // コマンドを打つとコマンド(size filename)がそのまま帰ってくるので
  // 改行するところ(\r)までの文字列は無視．
  while(1){
    if(_serial->available()){
      char c = _serial->read();
      if(c == '\r') break;
    }
  }

  while(1){
    while(_serial->available()){
      char c = _serial->read();
      // ファイルが使われていない場合は-1が返ってくるので - で判定
      if(c == '-') return false;
      // それ以外は使われているということ
      if(c == '>')  return true;
    }
  }
}
