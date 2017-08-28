/**
  @file radio.cpp
  @author Kandai Watanabe
  @date Created: 20170506
*/
#include "radio.h"

Radio::Radio() {
  _serial = NULL;
}

Radio::~Radio() {
  _serial = NULL;
}

void Radio::setSerial(HardwareSerial *serial) {
  _serial = serial;
  xbee.setSerial(*_serial);
}

void Radio::receiveModuleData() {
  XBeeResponse response = XBeeResponse();
  ZBRxResponse rx = ZBRxResponse();
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_EXPLICIT_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(rx);
      if (xbee.getResponse().getFrameData()[4] == 0x40) {
        for (int i = 0; i < rx.getDataLength(); i++) {
          if (i == 10) {
            data1 = String(rx.getData()[i], DEC);
          }
          if (i == 11) {
            data2 = String(rx.getData()[i], DEC);
          }
        }
        intData1 = data1.toInt();
        intData2 = data2.toInt();
        moduleData1 = intData1 * 256 + intData2;

      } else if (xbee.getResponse().getFrameData()[4] == 0x41) {
        for (int i = 0; i < rx.getDataLength(); i++) {
          if (i == 10) {
            data1 = String(rx.getData()[i], DEC);
          }
          if (i == 11) {
            data2 = String(rx.getData()[i], DEC);
          }
        }
        intData1 = data1.toInt();
        intData2 = data2.toInt();
        moduleData2 = intData1 * 256 + intData2;
      }
    }
  }
}

void Radio::send(String s) {
  int len = s.length();
  uint8_t sendData[len];

  for (int i = 0; i < len; i++) {
    String tempstring = s.substring(i, i + 1);
    if (tempstring == ",") {
      sendData[i] = 44;
    } else if (tempstring == ".") {
      sendData[i] = 46;
    } else {
      sendData[i] = tempstring.toInt() + 48;
    }
  }

  XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x00000000);
  ZBTxRequest zbTx = ZBTxRequest(addr64, sendData, sizeof(sendData));
  xbee.send(zbTx);
  Serial.println(F("Sent to XBee!"));
}
