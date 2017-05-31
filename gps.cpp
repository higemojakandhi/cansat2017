/**
* @file gps.cpp
* @author Kandai Watanabe
* @date Created: 20170524
*/
#include "gps.h"

Gps::Gps(){
}

Gps::~Gps(){
}

void Gps::setSerial(HardwareSerial* serial){
  _serial = NULL;
  _serial = serial;
}

void Gps::readGpsValue(){
  int count = 0;
  float t, latDeg, latMin, lonDeg, lonMin, satNum, posAccuracy, alt, latDegReal, latMinReal, lonDegReal, lonMinReal;

  do {
    if (_serial->available()) {
      _buf[count] = _serial->read();
      count++;
    }
    if (count >= 200 )break;     //バッファが溢れそうなら強制的に1行終了
  } while (_buf[count - 1] != 0x0A);
  _buf[count] = '\0';

  /////ここまでで生データをバッファに格納
  /////ここからGPGGA情報を抽出
  /////例　$GPGGA,085120.370,3541.1493,N,13945.3994,E,~,
  /////とりあえず表示だけ
  if (0 == strncmp("$GPGGA", _buf, 6)) { //先頭6文字を比較
    strtok(_buf, ",");
    t = atof(strtok(NULL, ","));       // UTC時刻の抽出
    latDeg = atof(strtok(NULL, "."));        // 緯度の度
    latMin = atof(strtok(NULL, ","));      // 緯度の分
    strtok(NULL, ",");       // N or S
    lonDeg = atof(strtok(NULL, "."));       // 経度の度
    lonMin = atof(strtok(NULL, ","));       // 経度の分
    strtok(NULL, ",");       // E or W
    strtok(NULL, ",");
    satNum = (short)atof(strtok(NULL, ","));     // The number of Satellites
    posAccuracy = atof(strtok(NULL, ","));// The accuracy of its position
    alt = atof(strtok(NULL, ","));     // The height


    latDegReal = (long)latDeg / 100;
    latMinReal = round(( (latDeg / 100 - latDegReal) * 100 + latMin / 10000) / 60 * 1000000);
    _lat = latDegReal*1000000 + latMinReal;
    lonDegReal = (long)lonDeg / 100;
    lonMinReal = round(( (lonDeg / 100 - lonDegReal) * 100 + lonMin / 10000) / 60 * 1000000);
    _lon = lonDegReal*1000000 + lonMinReal;
  }
}

void Gps::saveGpsValue(){
}

void Gps::showGpsValue(){
  Serial.print("Longitude= ");
  Serial.println(_lon);
  Serial.print("Latitude= ");
  Serial.println(_lat);
}
