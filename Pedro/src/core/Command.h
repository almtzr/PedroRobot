#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>

struct Command {
    uint8_t previousLed;
    uint8_t currentLed;
    uint8_t rotation;
};

#endif
