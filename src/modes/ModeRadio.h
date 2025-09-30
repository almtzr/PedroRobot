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
    void startRadio(RadioSettings radioSet);
    void update();
    void setRadioEncode(RadioMessage radioMsg);
    RadioMessage getRadioDecode();
  private:
    RF24* m_radio;
    bool m_radioActive;
    RadioSettings m_radioSet;
    RadioMessage m_radioEncode;
    RadioMessage m_radioDecode;
};

#endif
