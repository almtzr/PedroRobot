#include "ManageDisplay.h"

void ManageDisplay::Init() {
    m_currentScreen = SCREEN_INTRO;
    m_selectedMode = MODE_NORMAL;
    m_radioType = 0;
    m_radioSelect = 0;
    m_radioKey = 1;
    Serial.print("Mode sélectionné: ");
    Serial.println(m_selectedMode);
}

void ManageDisplay::setDisplayScreen(ScreenType screen) {
    m_currentScreen = screen;
}

ScreenType ManageDisplay::getScreen() const {
    return m_currentScreen;
}

void ManageDisplay::setModeActivated(const char* mode) {
    Serial.print("Mode activé: ");
    Serial.println(mode);
}

void ManageDisplay::setModeSelected(ModeType mode) {
    m_selectedMode = mode;
    Serial.print("Mode sélectionné: ");
    Serial.println(mode);
}

void ManageDisplay::setRadioType(uint8_t type) {
    m_radioType = type;
    Serial.print("Radio type: ");
    Serial.println(type);
}

void ManageDisplay::setRadioSelected(uint8_t select) {
    m_radioSelect = select;
    Serial.print("Radio sélection: ");
    Serial.println(select);
}

void ManageDisplay::setRadioKey(uint8_t key) {
    m_radioKey = key;
    Serial.print("Radio key: ");
    Serial.println(key);
}
