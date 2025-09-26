#include "ManageState.h"
#include "ManageButton.h"
#include "ManageDisplay.h"
#include "ManageMove.h"
#include "modes/ModeRadio.h"
#include "modes/ModeBluetooth.h"


ManageState::ManageState() {
    m_currentScreen = ScreenType::INTRO;
    m_currentMode = ModeType::NORMAL;
    m_previousMillis = 0;
    m_intervalIntro = 3000; // 3s intro
    m_selectRadio = 1;
    m_ignoreButtons = false;
    m_radioSet.radioCode = 1;
    m_radioSet.radioType = RadioType::TX;
    m_radioEncode.currentLed = 0;
    m_radioEncode.rotation = 0;
    m_radioDecode.currentLed = -1;
    m_radioDecode.rotation = 0;
    m_servoSet.pulse = 0;
    m_servoSet.servoId = 0;
    m_button = {false,false,false,false,false,false};
}

bool ManageState::allButtonsReleased(ManageButton* btn) {
    return !btn->getBtnCenterClick() &&
           !btn->getBtnCenterPress() &&
           !btn->getBtnRightClick()  &&
           !btn->getBtnRightPress()  &&
           !btn->getBtnLeftClick()   &&
           !btn->getBtnLeftPress();
}

void ManageState::update(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeBluetooth* bluetooth) {

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
        case ScreenType::CONTROL:        screenControl(display, move, radio, bluetooth); break;
        case ScreenType::SELECT_MODE:    screenSelectMode(display, move); break;
        case ScreenType::RADIO_SETTINGS: screenRadio(display, radio); break;
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

void ManageState::screenControl(ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeBluetooth* bluetooth) {

    if (m_button.btnCenterPress) {
        screenTransition(ScreenType::SELECT_MODE, display);
        radio->stopRadio();
        bluetooth->stopBluetooth();
    }

    switch (m_currentMode) {
        case ModeType::NORMAL:    modeNormal(move); break;
        case ModeType::RECORD:    modeRecord(move); break;
        case ModeType::REPLAY:    modeReplay(move); break;
        case ModeType::WEBCTRL:   modeWebctrl(move); break;
        case ModeType::BLUETOOTH: modeBluetooth(move, bluetooth); break;
        case ModeType::RADIO:     modeRadio(move, radio); break;
    }
}

void ManageState::screenSelectMode(ManageDisplay* display, ManageMove* move) {
    if (m_button.btnRightClick) {
        m_currentMode = static_cast<ModeType>(
            (static_cast<uint8_t>(m_currentMode) + 1) % static_cast<uint8_t>(ModeType::COUNT)
        );
    } else if (m_button.btnLeftClick) {
        m_currentMode = static_cast<ModeType>(
            (static_cast<uint8_t>(m_currentMode) + static_cast<uint8_t>(ModeType::COUNT) - 1) % static_cast<uint8_t>(ModeType::COUNT)
        );
    }

    if (m_button.btnCenterClick) {
        if (m_currentMode == RECORD) {
             move->initRecord();
        }
        if (m_currentMode == RADIO) {
            screenTransition(ScreenType::RADIO_SETTINGS, display);
        } else {
            screenTransition(ScreenType::CONTROL, display);
        }
    }
    display->setModeSelected(m_currentMode);
}


void ManageState::screenRadio(ManageDisplay* display, ModeRadio* radio) {

    if (m_selectRadio == 1) {
        if (m_button.btnRightClick) {
            if (m_radioSet.radioType == TX){
                m_radioSet.radioType = RX;
            } else if (m_radioSet.radioType == RX) {
                m_radioSet.radioType = TX;
            }
            display->setRadioType(m_radioSet.radioType);
        }
        if (m_button.btnCenterClick) {
            Serial.println("CENTER ON");
            m_selectRadio++;
            display->setRadioSelected (m_selectRadio);
        }
    } else if (m_selectRadio == 2) {
        if (m_button.btnRightPress) {
            if (m_radioSet.radioCode < 100) {
                m_radioSet.radioCode++;
            }
        } else if (m_button.btnLeftPress) {
            if (m_radioSet.radioCode > 1) {
                m_radioSet.radioCode--;
            }
        }
        display->setRadioKey (m_radioSet.radioCode);      
        if (m_button.btnCenterClick) {
            m_selectRadio++;
            display->setRadioSelected (m_selectRadio);  
        }
    } else if (m_selectRadio == 3) {
        if (m_button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            radio->startRadio(m_radioSet);
        }
    }
}

void ManageState::modeNormal(ManageMove* move) {  
    if (m_button.btnCenterClick) {
        if (m_servoSet.servoId < 3) {
            m_servoSet.servoId++;
        } else if (m_servoSet.servoId == 3) {
            m_servoSet.servoId = 0;
        }
        move->setCurrentLED(m_servoSet.servoId);
    } 

    m_servoSet.pulse = 0;
    
    if (m_button.btnLeftPress) {
        Serial.println("LEFT...");
        m_servoSet.pulse = 4;
        m_radioEncode.rotation = 20;
    } else if (m_button.btnRightPress) {
        Serial.println("RIGHT...");
        m_servoSet.pulse = 8;
        m_radioEncode.rotation = 10;
    } 

    move->setServoSettings(m_servoSet);
}

void ManageState::modeRecord(ManageMove* move) {  
    modeNormal(move);
}

void ManageState::modeReplay(ManageMove* move) {  
   // do {
        move->startReplay();
   // } while (not m_button.btnCenterPress);
}

void ManageState::modeRadio(ManageMove* move, ModeRadio* radio) {  
    if (m_radioSet.radioType == TX){  
        Serial.println("Radio TX");
        m_radioEncode.rotation = 30;
        modeNormal(move);        
        m_radioEncode.currentLed = m_servoSet.servoId;
        radio->setRadioEncode(m_radioEncode);
    } else if (m_radioSet.radioType == RX) {
        m_radioDecode = radio->getRadioDecode();
        move->setCurrentLED(m_radioDecode.currentLed);
        m_servoSet.pulse = 0;
        m_servoSet.servoId = m_radioDecode.currentLed; 
        if (m_radioDecode.rotation == 20) {
            m_servoSet.pulse = 4;
            m_servoSet.servoId = m_radioDecode.currentLed;
          //  move->rotationLeft(m_radioDecode.currentLed);
        } else if (m_radioDecode.rotation == 10) {
            m_servoSet.pulse = 8;
            m_servoSet.servoId = m_radioDecode.currentLed;
           // move->rotationRight(m_radioDecode.currentLed);
        } 
        move->setServoSettings(m_servoSet);
    }
}

void ManageState::modeWebctrl(ManageMove* move) {
    static char command[4];   // 2 chars + '\n' + '\0'
    static uint8_t index = 0;

    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n') {
            command[index] = '\0';  // terminer la chaîne

            if (index >= 2) {       // au moins 2 caractères valides
                m_servoSet.servoId = command[0] - '1';
                char direction = command[1];

                // DEBUG
                Serial.print(F("Dir: "));
                Serial.println(direction);

                move->setCurrentLED(m_servoSet.servoId);

                if (direction == 'L') m_servoSet.pulse = 4;
                else if (direction == 'R') m_servoSet.pulse = 8;
                else m_servoSet.pulse = 0;

                move->setServoSettings(m_servoSet);
            }

            index = 0; // reset pour le prochain message
        } 
        else if (index < sizeof(command) - 1) {
            command[index++] = c;
        }
        else {
            // si trop long => reset
            index = 0;
        }
    }
    
}

void ManageState::modeBluetooth(ManageMove* move, ModeBluetooth* bluetooth) {  

    if (m_currentMode == BLUETOOTH) {
        bluetooth->startBluetooth();
    }

    m_radioDecode = bluetooth->getRadioDecode();
    move->setCurrentLED(m_radioDecode.currentLed);
    m_servoSet.pulse = 0;
    m_servoSet.servoId = m_radioDecode.currentLed; 
    if (m_radioDecode.rotation == 20) {
        m_servoSet.pulse = 4;
    } else if (m_radioDecode.rotation == 10) {
        m_servoSet.pulse = 8;
    } 
    move->setServoSettings(m_servoSet);
}

