#ifndef MODE_RADIO_H
#define MODE_RADIO_H

#include <Arduino.h>
#include "config/Config.h"
#include <RF24.h>

class ManageMove;

class ModeRadio {
  public:
    ModeRadio();
    void init();
    void stopRadio();
    void initRadio();
    void startRadio(TransmissionSettings radioSet);
    void update();
    void setRadioEncode(PedroMessage radioMsg);
    PedroMessage getRadioDecode();
  private:
    RF24* m_radio;
    bool m_radioActive;
    TransmissionSettings m_radioSet;
    PedroMessage m_messageEncode;
    PedroMessage m_messageDecode;
};

#endif
