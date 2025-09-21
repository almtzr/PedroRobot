#include "ManageState.h"
#include "ManageButton.h"
#include "ManageDisplay.h"
#include "ManageMove.h"
#include "modes/ModeRadio.h"


ManageState::ManageState() {
    m_currentScreen = ScreenType::INTRO;
    m_currentMode = ModeType::NORMAL;
    m_previousMillis = 0;
    m_intervalIntro = 3000; // 3s intro
    m_selectMode = 1;
    m_selectRadio = 1;
    m_servoId = 0;
    m_btnCenterLongPress = false;
    m_ignoreButtons = false;
    m_radioSet.radioCode = 1;
    m_radioSet.radioType = RadioType::TX;
    m_radioEncode.currentLed = 0;
    m_radioEncode.rotation = 0;
    m_radioDecode.currentLed = -1;
    m_radioDecode.rotation = 0;
}

bool ManageState::allButtonsReleased(ManageButton* btn) {
    return !btn->getBtnCenterClick() &&
           !btn->getBtnCenterPress() &&
           !btn->getBtnRightClick()  &&
           !btn->getBtnRightPress()  &&
           !btn->getBtnLeftClick()   &&
           !btn->getBtnLeftPress();
}

void ManageState::updateState(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio) {

    if (m_ignoreButtons) {
        if (allButtonsReleased(btn)) {
            m_ignoreButtons = false; 
        }
        m_button = {};
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
        case ScreenType::INTRO:          screenIntro(display); break;
        case ScreenType::CONTROL:        screenControl(m_button, display, move, radio); break;
        case ScreenType::SELECT_MODE:    screenSelectMode(m_button, display); break;
        case ScreenType::RADIO_SETTINGS: screenRadio(m_button, display, radio); break;
    }
}

void ManageState::screenTransition(ScreenType screenType, ManageDisplay* display) {
    m_ignoreButtons = true;
    m_currentScreen = screenType;
    m_selectRadio = 1;
    display->setRadioSelected (m_selectRadio);
    display->setDisplayScreen(m_currentScreen);
}

void ManageState::screenIntro(ManageDisplay* display) {
    if (millis() - m_previousMillis >= m_intervalIntro) {
        screenTransition(ScreenType::CONTROL, display);
        m_previousMillis = millis();
    }
}

void ManageState::screenControl(Button button, ManageDisplay* display, ManageMove* move, ModeRadio* radio) {

    if (button.btnCenterPress) {
        screenTransition(ScreenType::SELECT_MODE, display);
        radio->stopRadio();
    }

    switch (m_currentMode) {
        case ModeType::NORMAL:    modeNormal(button, move); break;
        case ModeType::RECORD:    modeRecord(button, move); break;
        case ModeType::REPLAY:    modeReplay(button, move); break;
        case ModeType::WEBCTRL:   modeWebctrl(button, move); break;
        case ModeType::BLUETOOTH: modeBluetooth(button, move); break;
        case ModeType::RADIO:     modeRadio(button, move, radio); break;
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


void ManageState::screenRadio(Button button, ManageDisplay* display, ModeRadio* radio) {

    if (m_selectRadio == 1) {
        if (button.btnRightClick) {
            if (m_radioSet.radioType == TX){
                m_radioSet.radioType = RX;
            } else if (m_radioSet.radioType == RX) {
                m_radioSet.radioType = TX;
            }
            display->setRadioType(m_radioSet.radioType);
        }
        if (button.btnCenterClick) {
            Serial.println("CENTER ON");
            m_selectRadio++;
            display->setRadioSelected (m_selectRadio);
        }
    } else if (m_selectRadio == 2) {
        if (button.btnRightPress) {
            if (m_radioSet.radioCode < 100) {
                m_radioSet.radioCode++;
            }
        } else if (button.btnLeftPress) {
            if (m_radioSet.radioCode > 1) {
                m_radioSet.radioCode--;
            }
        }
        display->setRadioKey (m_radioSet.radioCode);      
        if (button.btnCenterClick) {
            m_selectRadio++;
            display->setRadioSelected (m_selectRadio);  
        }
    } else if (m_selectRadio == 3) {
        if (button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            radio->setRadioSettings(m_radioSet);
        }
    }
}

void ManageState::modeNormal(Button button, ManageMove* move) {  
    if (button.btnCenterClick) {
        if (m_servoId < 3) {
            m_servoId++;
        } else if (m_servoId == 3) {
            m_servoId = 0;
        }
        move->setCurrentLED(m_servoId);
    } else if (button.btnLeftPress) {
        move->rotationLeft(m_servoId);
        m_radioEncode.rotation = 20;
    } else if (button.btnRightPress) {
        move->rotationRight(m_servoId);
        m_radioEncode.rotation = 10;
    } else {
        move->servoIDLE(m_servoId);
    }
}

void ManageState::modeRecord(Button button, ManageMove* move) {  
    modeNormal(button, move);
}

void ManageState::modeReplay(Button button, ManageMove* move) {  
}

void ManageState::modeRadio(Button button, ManageMove* move, ModeRadio* radio) {  
    if (m_radioSet.radioType == TX){  
        Serial.println("Radio TX");
        m_radioEncode.rotation = 30;
        modeNormal(button, move);        
        m_radioEncode.currentLed = m_servoId;
        radio->setRadioEncode(m_radioEncode);
    } else if (m_radioSet.radioType == RX) {
        m_radioDecode = radio->getRadioDecode();
        move->setCurrentLED(m_radioDecode.currentLed);
        if (m_radioDecode.rotation == 20) {
            move->rotationLeft(m_radioDecode.currentLed);
        } else if (m_radioDecode.rotation == 10) {
            move->rotationRight(m_radioDecode.currentLed);
        } else {
            move->servoIDLE(m_radioDecode.currentLed);
        }
    }
}

void ManageState::modeWebctrl(Button button, ManageMove* move) {  
}

void ManageState::modeBluetooth(Button button, ManageMove* move) {  
}

