/**
* @file nineaxis.cpp
* @author Kandai Watanabe
* @date Created: 20170524
*/
#include "nineaxis.h"

NineAxis::NineAxis(){
  _accelX=_accelY=_accelZ=0;
  _gyroX=_gyroY=_gyroZ=0;
  _magX=_magY=_magZ=0;
  _pitch=_roll=_yaw=0;
  _deg=0;
}

NineAxis::~NineAxis(){
}

void NineAxis::init(){
  if(imu.begin() == INV_SUCCESS){
      Serial.println(F("configured MPU-9250"));
  }else{
    while (1)
    {
      Serial.println("Unable to communicate with MPU-9250");
      Serial.println("Check connections, and try again.");
      Serial.println();
      delay(5000);
    }
  }

  imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
  imu.setAccelFSR(16);
  imu.setLPF(10);
  imu.dmpBegin( DMP_FEATURE_SEND_RAW_ACCEL |
                DMP_FEATURE_GYRO_CAL |
                DMP_FEATURE_SEND_CAL_GYRO |
                DMP_FEATURE_6X_LP_QUAT,
                10);
}

void NineAxis::readNineAxisValue(){
  if ( imu.fifoAvailable() ){
    if ( imu.dmpUpdateFifo() == INV_SUCCESS){
      _accelX = imu.calcAccel(imu.ax);
      _accelY = imu.calcAccel(imu.ay);
      _accelZ = imu.calcAccel(imu.az);
      convertAccel(&_accelX, &_accelY, &_accelZ);
      _gyroX = imu.calcGyro(imu.gx);
      _gyroY = imu.calcGyro(imu.gy);
      _gyroZ = imu.calcGyro(imu.gz);
      _magX = imu.calcMag(imu.mx);
      _magY = imu.calcMag(imu.my);
      _magZ = imu.calcMag(imu.mz);
      imu.computeEulerAngles(true); // true=degree, false=rad
      _pitch = imu.pitch;
      _roll = imu.roll;
      _yaw = imu.yaw;
      _deg = imu.computeCompassHeading();
    }
  }
}

void NineAxis::convertAccel(float* x, float* y, float* z){
  *x = (*x)*9.8;
  *y = (*y)*9.8;
  *z = (*z)*9.8;
}
