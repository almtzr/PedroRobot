#include <PedroRobot.h>

ManageState manageState;
ManageButton manageButton;
ManageDisplay manageDisplay;
ManageMove manageMove;
ModeRadio modeRadio;

void setup() {
    Serial.begin(9600);
    manageButton.Init();
    manageDisplay.Init();
    manageMove.Init();
    modeRadio.Init();
}

void loop() {
    manageButton.update();    
    manageDisplay.updateDisplay();
    manageState.updateState(&manageButton, &manageDisplay, &manageMove, &modeRadio);
    modeRadio.radioRXTX();
    manageMove.updateServo();
}
