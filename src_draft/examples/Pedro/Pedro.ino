#include <PedroRobot.h>

ManageState manageState;
ManageButton manageButton;
ManageDisplay manageDisplay;

void setup() {
    Serial.begin(115200);
    manageButton.Init();
    manageDisplay.Init();
    manageState.Init();
}

void loop() {
    manageButton.update();
    manageState.updateState(&manageButton, &manageDisplay);
    manageDisplay.updateDisplay();
}
