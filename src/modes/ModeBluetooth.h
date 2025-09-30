#ifndef MODE_BLUETOOTH_H
#define MODE_BLUETOOTH_H

#include <Arduino.h>
#include "config/Config.h"

class ModeBluetooth {
  public:
    ModeBluetooth();
    void update();
    EnableATmode enableATmode();
    void startBluetooth(RadioSettings radioSet);
    void stopBluetooth();
    void setRadioEncode(RadioMessage radioMsg);
    RadioMessage getRadioDecode();

  private:
    EnableATmode m_enableATmode;
    bool m_bluetoothActive;
    RadioSettings m_radioSet;
    RadioMessage m_radioDecode;
};

#endif
