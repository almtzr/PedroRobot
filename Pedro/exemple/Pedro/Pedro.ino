#include <PedroRobot.h>

ManageState manageState;
ManageButton manageButton;
ManageDisplay manageDisplay;
ManageMove manageMove;
ModeRadio modeRadio;
ModeBluetooth modeBluetooth;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    manageButton.init();
    manageDisplay.init();
    manageMove.init();
    modeRadio.init();
    modeBluetooth.init();
}

void loop() {
    manageButton.update();    
    manageDisplay.updateDisplay();
    manageState.update(&manageButton, &manageDisplay, &manageMove, &modeRadio, &modeBluetooth);
    modeRadio.update();
    modeBluetooth.update();
    manageMove.moveServo();
}
