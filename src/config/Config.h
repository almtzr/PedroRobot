#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

extern char buffer[32];
extern char bufferBT[3];     // buffer réception (2 chiffres + '\0')
extern uint8_t idx;          // index du buffer

// Types d’écran
enum ScreenType : uint8_t {
    INTRO,
    CONTROL,
    SELECT_MODE,
    RADIO_SETTINGS,
    BLUETOOTH_SETTINGS,
    BLUETOOTH_UPDATE
};

enum ModeType : uint8_t {
    MANUAL,
    RECORD,
    REPLAY,
    USBSERIAL,
    BLUETOOTH,
    RADIO,
    COUNT
};

enum RadioType : uint8_t {
    TX,
    RX
};

enum EnableATmode : uint8_t {
    OK,
    KO,
    NA
};

enum SetParam : uint8_t {
    PARAM1,
    PARAM2,
    PARAM3,
    PARAM4
};

struct RadioMessage {
    byte currentLed;
    byte rotation;
};

struct ServoSettings {
    uint8_t servoId;
    uint8_t pulse;
};


struct RadioSettings {
    RadioType radioType;
    uint8_t radioCode;
};

// Pins
#define RELEASE "v1.0.1" 
#define TITLE_DLE "PEDRO ROBOT" 
#define TITLE_MODE "SELECT MODE" 
#define TITLE_RADIO "RADIO SETTINGS"
#define TITLE_BLUETOOTH "BLUETOOTH SETTINGS"
#define TITLE_BLUETOOTH_UPDATE "BLUETOOTH UPDATE"

#define TYPE_TX "TRANSMITTER" 
#define TYPE_RX "RECEIVER" 

#define BTN_LEFT   A2
#define BTN_CENTER A0
#define BTN_RIGHT  A1

#define LEVELWIDTH 17
#define LEVELWIDTH_ 13
#define SCREEN_SIZE_X 128
#define SCREEN_SIZE_Y 64
#define TIME1 3000
#define TIME2 10

constexpr uint8_t LED_PINS[4]   = {13, 11, 8, 7};
constexpr uint8_t SERVO_PINS[4] = {5, 6, 9, 10};

#endif
