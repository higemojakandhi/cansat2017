/**
* @file nineaxis.cpp
* @author Kandai Watanabe
* @date Created: 20170524
*/
#include "nineaxis.h"

NineAxis::NineAxis(){
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
  fabo_9axis.readGyroXYZ(&_gx,&_gy,&_gz);
  fabo_9axis.readMagnetXYZ(&_mx,&_my,&_mz);
  fabo_9axis.readTemperature(&_temp);
  _deg = atan2(_my,_mx)*180/PI;
}

void NineAxis::showNineAxisValue(){

  Serial.print("Digital Compass Angle [deg] ");
  Serial.println(_deg);
}
