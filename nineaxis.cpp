/**
* @file nineaxis.cpp
* @author Kandai Watanabe
* @date Created: 20170524
*/
#include "nineaxis.h"

NineAxis::NineAxis(){
  _ax=_ay=_az=0;
  _gx=_gy=_gz=0;
  _mx=_my=_mz=0;
  _temp=0;
  _deg=0;
}

NineAxis::~NineAxis(){
}

void NineAxis::init(){
    if (fabo_9axis.begin()) {
      Serial.println("configured FaBo 9Axis I2C Brick");
    } else {
      Serial.println("device error");
      while(1);
    }
}

void NineAxis::readNineAxisValue(){
  fabo_9axis.readAccelXYZ(&_ax,&_ay,&_az);
  convertAccel(&_ax, &_ay, &_az);
  fabo_9axis.readGyroXYZ(&_gx,&_gy,&_gz);
  fabo_9axis.readMagnetXYZ(&_mx,&_my,&_mz);
  fabo_9axis.readTemperature(&_temp);
  _deg = calcDegree(_my, _mx);
}

void NineAxis::printNineAxisValue(){
  Serial.print("Digital Compass Angle [deg] ");
  Serial.println(_deg);
}


float NineAxis::calcDegree(float a, float b){
  float result;
  result = atan2(a,b)*180/PI;
  return result;
}

void NineAxis::convertAccel(float* x, float* y, float* z){
  *x = (*x)*9.8;
  *y = (*y)*9.8;
  *z = (*z)*9.8;
}
