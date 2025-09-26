#ifndef MODE_BLUETOOTH_H
#define MODE_BLUETOOTH_H

#include <Arduino.h>
#include "config/Config.h"

class ModeBluetooth {
  public:
    ModeBluetooth();
    void init();
    void update();
    void startBluetooth();
    void stopBluetooth();
    void setRadioEncode(RadioMessage radioMsg);
    RadioMessage getRadioDecode();

  private:
    bool m_bleutoothActive;
    RadioMessage m_radioDecode;
};

#endif
