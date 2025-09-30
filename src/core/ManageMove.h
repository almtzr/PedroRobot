#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "config/Config.h"

struct Movement {
    int pulse;
    unsigned long duration;
    uint8_t servo;
};

class ManageMove {
  public:
    ManageMove();
    void init();
    void LEDOFF();
    void servoIDLE(uint8_t servoId);
    void setCurrentLED(uint8_t LEDId);
    void setServoSettings(ServoSettings servoSet);
    void update();
    void recordMove();
    void eraseMovement();
    void initRecord();
    void startRecord();
    void startReplay();

  private:
    static const uint8_t MAX_MOVEMENTS = 50;
    Movement m_movements[MAX_MOVEMENTS];
    ServoSettings m_servoSet;
    int16_t m_lastPulse;
    uint8_t m_index;
    uint8_t m_currentLED;
    unsigned long m_previousMillis;
    bool  m_startRecord;
};

#endif
