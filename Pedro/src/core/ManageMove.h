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
    void Init();
    void LEDOFF();
    void servoIDLE(uint8_t servoId);
    void setCurrentLED(uint8_t LEDId);
    void AddMovement(int pulse, unsigned long duration, uint8_t servo);
    void Replay();
    void setServoSettings(ServoSettings servoSet);
    void updateServo();

  private:
    static const uint8_t MAX_MOVEMENTS = 40;
    Movement m_movements[MAX_MOVEMENTS];
    ServoSettings m_servoSet;
    uint8_t m_index;
    uint8_t m_currentLED;
};

#endif
