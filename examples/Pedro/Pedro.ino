// ========================================================================================
//  File             : Pedro.ino
//  Description      : Firmware to directly control the Pedro Robot in the following modes: 
//                     Manual, Radio, Bluetooth, Replay, Record, and USB Serial.                  
//  Supported Boards : Pedro Rev3
//  Servo Type       : 360° SG90 or MG90
//  GitHub Repo      : https://github.com/almtzr/PedroRobot
//  Author           : Almoutazar SAANDI
//  Date             : Oct 21, 2025
//  Last Update      : v1.0.1
// ========================================================================================

#include <PedroRobot.h>

ManageState manageState;
ManageButton manageButton;
ManageDisplay manageDisplay;
ManageMove manageMove;
ModeRadio modeRadio;
ModeBluetooth modeBluetooth;

void setup() {
    Serial.begin(9600);
    Serial1.begin(38400);
    manageButton.init();
    manageDisplay.init();
    manageMove.init();
    modeRadio.init();
}

void update() {
    manageButton.update();    
    manageDisplay.update();
    modeRadio.update();
    modeBluetooth.update();
    manageMove.update();
}

void loop() {
    update();    
    manageState.update(&manageButton, &manageDisplay, &manageMove, &modeRadio, &modeBluetooth);
}
