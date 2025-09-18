#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>

struct Movement {
    int pulse;
    unsigned long duration;
    uint8_t servo;
};

class MovementManager {
  public:
    void Init();
    void StartRecord();
    void AddMovement(int pulse, unsigned long duration, uint8_t servo);
    void Replay();

  private:
    static const uint8_t MAX_MOVEMENTS = 100;
    Movement m_movements[MAX_MOVEMENTS];
    uint8_t m_index;
};

#endif
