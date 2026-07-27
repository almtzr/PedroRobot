#ifndef MODE_BLUETOOTH_H
#define MODE_BLUETOOTH_H

#include <Arduino.h>
#include "config/Config.h"

class ModeUART {
  public:
    ModeUART();
    void update();
    EnableATmode enableATmode();
    void startBluetooth(TransmissionSettings bluetoothSet, TransmissionType roleUART);
    void stopBluetooth();
    void setUARTMessage(PedroMessage uartMsg);
    PedroMessage getUARTMessage();

  private:
    EnableATmode m_enableATmode;
    bool m_bluetoothActive;
    TransmissionSettings m_bluetoothSet;
    TransmissionType m_roleUART;
    PedroMessage m_messageDecode;
    PedroMessage m_messageEncode;
};

#endif
