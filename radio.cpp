/**
* @file radio.cpp
* @author Kandai Watanabe
* @date Created: 20170506
*/
#include "radio.h"

Radio::Radio(){
  _serial = NULL;
}

Radio::~Radio(){
}

void Radio::setSerial(HardwareSerial *serial){
  _serial = serial;
  xbee.setSerial(*_serial);
}

void Radio::send(String s){
  int len = s.length();
  uint8_t sendData[len];

  for(int i=0; i<len; i++){
    String tempstring = s.substring(i,i+1);
    if(tempstring==","){
      sendData[i]=44;
    }else if(tempstring=="."){
      sendData[i]=46;
    }else{
      sendData[i]=tempstring.toInt()+48;
    }
  }

  XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x00000000);
  ZBTxRequest zbTx = ZBTxRequest(addr64, sendData, sizeof(sendData));
  xbee.send(zbTx);

  delay(1000);
}
