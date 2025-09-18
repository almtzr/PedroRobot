#include "ManageState.h"
#include "ManageButton.h"
#include "ManageDisplay.h"

ManageState::ManageState() {
    m_currentScreen = Screen::INTRO;
    m_previousMillis = 0;
    m_intervalIntro = 3000; // 3s intro
    m_selectMode = 1;
    m_selectRadio = 1;
    m_radioKey = 1;
    m_btnCenterLongPress = false;
    m_btnLeft = false;
    m_btnRight = false;
}

void ManageState::Init() {}

void ManageState::updateState(ManageButton* btn, ManageDisplay* display) {
    switch (m_currentScreen) {
        case Screen::INTRO:       screenIntro(); break;
        case Screen::CONTROL:     screenControl(btn, display); break;
        case Screen::SELECT_MODE: screenSelectMode(btn, display); break;
        case Screen::RADIO:       screenRadio(); break;
    }
}

void ManageState::screenIntro() {
    if (millis() - m_previousMillis >= m_intervalIntro) {
        m_currentScreen = Screen::CONTROL;
        m_previousMillis = millis();
    }
}

void ManageState::screenControl(ManageButton* btn, ManageDisplay* display) {
    m_btnLeft = btn->getBtnLeftState();
    m_btnRight = btn->getBtnRightState();
    m_btnCenterLongPress = btn->getBtnCenterLongPress();
    if (m_btnCenterLongPress) {
        m_currentScreen = Screen::SELECT_MODE;
        display->setDisplayScreen(ScreenType::SCREEN_SELECT_MODE);
    }
    if (m_btnLeft) {
        Serial.println("Move Left: ");
    }
    if (m_btnRight) {
        Serial.println("Move Right: ");
    }

}
void ManageState::screenSelectMode(ManageButton* btn, ManageDisplay* display) {
        display->setModeSelected(ModeType::MODE_NORMAL);


}
void ManageState::screenRadio() {}
