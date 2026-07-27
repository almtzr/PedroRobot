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
    UART_SETTINGS,
    USB_SETTINGS,
    BLUETOOTH_SETTINGS,
    BLUETOOTH_UPDATE,
    BLUETOOTH_ERROR
};

enum ModeType : uint8_t {
    MANUAL,
    RECORD,
    REPLAY,
    USBSERIAL,
    BLUETOOTH,
    RADIO,
    UART,
    COUNT
};

enum TransmissionType : uint8_t {
    TX,
    RX,
    NE
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
    PARAM4,
    PARAM5,
    PARAMOK,
    PARAMUPDATE,
    PARAMX
};

struct PedroMessage {
    uint8_t currentLed;
    uint8_t rotation;
};

struct ServoSettings {
    uint8_t servoId;
    uint8_t pulse;
};


struct TransmissionSettings {
    TransmissionType role;
    uint8_t code;
};

// Pins
#define RELEASE "v1.0.4" 
#define TITLE_DLE "PEDRO ROBOT" 
#define TITLE_MODE "SELECT MODE" 
#define TITLE_RADIO "RADIO SETTINGS"
#define TITLE_UART "UART SETTINGS"
#define TITLE_USB "USB SETTINGS"
#define TITLE_BLUETOOTH "BLUETOOTH SETTINGS"
#define TITLE_BLUETOOTH_ERROR "BLUETOOTH ERROR"

#define TYPE_TX "TRANSMITTER" 
#define TYPE_RX "RECEIVER" 

#define BTN_CENTER A0
#define BTN_RIGHT  A1
#define BTN_LEFT   A2

#define LEVELWIDTH 17
#define LEVELWIDTH_ 13
#define SCREEN_SIZE_X 128
#define SCREEN_SIZE_Y 64
#define TIME1 3000
#define TIME2 10

constexpr uint8_t LED_PINS[4]   = {13, 11, 8, 7};
constexpr uint8_t SERVO_PINS[4] = {5, 6, 9, 10};

#endif
