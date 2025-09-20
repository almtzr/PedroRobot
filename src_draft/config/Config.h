#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Types d’écran
enum ScreenType : uint8_t {
    INTRO,
    CONTROL,
    SELECT_MODE,
    RADIO_SETTINGS
};

enum ModeType : uint8_t {
    NORMAL,
    RECORD,
    REPLAY,
    WEBCTRL,
    BLUETOOTH,
    RADIO,
    COUNT
};

// Pins
#define RELEASE "v.1.0.4" 
#define TITLE_DLE "PEDRO ROBOT" 
#define TITLE_MODE "SELECT MODE" 
#define TITLE_RADIO "RADIO SETTINGS"

#define TYPE_TX "TRANSMITTER" 
#define TYPE_RX "RECEIVER" 

#define BTN_LEFT   A2
#define BTN_CENTER A0
#define BTN_RIGHT  A1

#define LEVELWIDTH 17
#define LEVELWIDTH_ 13
#define SCREEN_SIZE_X 128
#define SCREEN_SIZE_Y 64


constexpr uint8_t LED_PINS[4]   = {13, 11, 8, 7};
constexpr uint8_t SERVO_PINS[4] = {5, 6, 9, 10};

#endif
