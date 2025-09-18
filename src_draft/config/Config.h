#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Pins

#define BTN_LEFT   A2
#define BTN_CENTER A0
#define BTN_RIGHT  A1


constexpr uint8_t LED_PINS[4]   = {13, 11, 8, 7};
constexpr uint8_t SERVO_PINS[4] = {5, 6, 9, 10};

#endif
