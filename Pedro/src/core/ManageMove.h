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
    void rotationRight(uint8_t servoId);
    void rotationLeft(uint8_t servoId);
    void AddMovement(int pulse, unsigned long duration, uint8_t servo);
    void Replay();

  private:
    static const uint8_t MAX_MOVEMENTS = 100;
    Movement m_movements[MAX_MOVEMENTS];
    uint8_t m_index;
    uint8_t m_currentLED;
};

#endif
