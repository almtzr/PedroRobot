#ifndef MODE_RADIO_H
#define MODE_RADIO_H

#include <Arduino.h>
#include <RF24.h>

class ModeRadio {
  public:
    void Init(RF24* radio);
    void startTx(const byte* address);
    void startRx(const byte* address);
    void stop();

  private:
    RF24* m_radio;
};

#endif
