#include "ManageState.h"
#include "ManageButton.h"
#include "ManageDisplay.h"


ManageState::ManageState() {
    m_currentScreen = ScreenType::INTRO;
    m_currentMode = ModeType::NORMAL;
    m_previousMillis = 0;
    m_intervalIntro = 3000; // 3s intro
    m_selectMode = 1;
    m_selectRadio = 1;
    m_radioKey = 1;
    m_btnCenterLongPress = false;
    m_ignoreButtons = false;
}

void ManageState::Init() {}

bool ManageState::allButtonsReleased(ManageButton* btn) {
    return !btn->getBtnCenterClick() &&
           !btn->getBtnCenterPress() &&
           !btn->getBtnRightClick()  &&
           !btn->getBtnRightPress()  &&
           !btn->getBtnLeftClick()   &&
           !btn->getBtnLeftPress();
}

void ManageState::updateState(ManageButton* btn, ManageDisplay* display) {

    if (m_ignoreButtons) {
        if (allButtonsReleased(btn)) {
            m_ignoreButtons = false; // Dès que tous relâchés → on réactive la lecture
        } else {
            m_button = {}; // reset à false
        }
    } else {
        // Lecture normale
        m_button.btnCenterClick = btn->getBtnCenterClick();
        m_button.btnCenterPress = btn->getBtnCenterPress();

        m_button.btnRightClick  = btn->getBtnRightClick();
        m_button.btnRightPress  = btn->getBtnRightPress();

        m_button.btnLeftClick   = btn->getBtnLeftClick();
        m_button.btnLeftPress   = btn->getBtnLeftPress();
    }

    switch (m_currentScreen) {
        case ScreenType::INTRO:       screenIntro(display); break;
        case ScreenType::CONTROL:     screenControl(m_button, display); break;
        case ScreenType::SELECT_MODE: screenSelectMode(m_button, display); break;
        case ScreenType::RADIO_SETTINGS:       screenRadio(); break;
    }
}

void ManageState::screenTransition(ScreenType screenType, ManageDisplay* display) {
    m_currentScreen = screenType;
    display->setDisplayScreen(m_currentScreen);
    m_ignoreButtons = true;
}

void ManageState::screenIntro(ManageDisplay* display) {
    if (millis() - m_previousMillis >= m_intervalIntro) {
        screenTransition(ScreenType::CONTROL, display);
        m_previousMillis = millis();
    }
}

void ManageState::screenControl(Button button, ManageDisplay* display) {

    if (button.btnCenterPress) {
        screenTransition(ScreenType::SELECT_MODE, display);
    }

    switch (m_currentMode) {
        case ModeType::NORMAL:    modeNormal(button); break;
        case ModeType::RECORD:    modeRecord(button); break;
        case ModeType::REPLAY:    modeReplay(button); break;
        case ModeType::WEBCTRL:   modeWebctrl(button); break;
        case ModeType::BLUETOOTH: modeBluetooth(button); break;
        case ModeType::RADIO:     modeRadio(button); break;
    }
}

void ManageState::screenSelectMode(Button button, ManageDisplay* display) {
    if (button.btnRightClick) {
        m_currentMode = static_cast<ModeType>(
            (static_cast<uint8_t>(m_currentMode) + 1) % static_cast<uint8_t>(ModeType::COUNT)
        );
    } else if (button.btnLeftClick) {
        m_currentMode = static_cast<ModeType>(
            (static_cast<uint8_t>(m_currentMode) + static_cast<uint8_t>(ModeType::COUNT) - 1) % static_cast<uint8_t>(ModeType::COUNT)
        );
    }

    if (button.btnCenterClick) {
        if (m_currentMode == RADIO) {
            screenTransition(ScreenType::RADIO_SETTINGS, display);
        } else {
            screenTransition(ScreenType::CONTROL, display);
        }
    }
    display->setModeSelected(m_currentMode);
}


void ManageState::screenRadio() {}

void ManageState::modeNormal(Button button) {  
    if (button.btnLeftPress) {
        Serial.println("Move Left: ");
    }
    if (button.btnRightPress) {
        Serial.println("Move Right: ");
    }
}

void ManageState::modeRecord(Button button) {  
    if (button.btnLeftPress) {
        Serial.println("Move Left: ");
    }
    if (button.btnRightPress) {
        Serial.println("Move Right: ");
    }
}

void ManageState::modeReplay(Button button) {  
}

void ManageState::modeRadio(Button button) {  
    if (button.btnLeftPress) {
        Serial.println("Move Left: ");
    }
    if (button.btnRightPress) {
        Serial.println("Move Right: ");
    }
}

void ManageState::modeWebctrl(Button button) {  
}

void ManageState::modeBluetooth(Button button) {  
}

