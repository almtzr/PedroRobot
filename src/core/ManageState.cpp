#include "ManageState.h"
#include "ManageButton.h"
#include "ManageDisplay.h"
#include "ManageMove.h"
#include "modes/ModeRadio.h"
#include "modes/ModeUART.h"

//static bool lastA3 = true;
//static bool lastA4 = true;
//static bool lastA5 = true;

ManageState::ManageState() {
    m_currentScreen = ScreenType::INTRO;
    m_currentMode = ModeType::MANUAL;
    m_param = SetParam::PARAM1;
    m_previousMillis = 0;
    m_ignoreButtons = false;
    m_radioSet.code = 1;
    m_radioSet.role = TransmissionType::TX;
    m_bluetoothSet.code = 1;
    m_bluetoothSet.role = TransmissionType::NE;
    m_roleUART = NE;
    m_messageEncode.currentLed = 0;
    m_messageEncode.rotation = 0;
    m_messageDecode.currentLed = -1;
    m_messageDecode.rotation = 0;
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

void ManageState::update(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeUART* uart) {

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
        case ScreenType::CONTROL:        screenControl(display, move, radio, uart); break;
        case ScreenType::SELECT_MODE:    screenSelectMode(display, move, uart); break;
        case ScreenType::RADIO_SETTINGS: screenRadio(display, radio); break;
        case ScreenType::UART_SETTINGS:  screenUART(display, uart); break;
        case ScreenType::USB_SETTINGS:   screenUSB(display, uart); break;
        case ScreenType::BLUETOOTH_SETTINGS: screenBluetooth(display, uart); break;
        case ScreenType::BLUETOOTH_ERROR: screenATMode(display, uart); break;
    }
}

void ManageState::screenTransition(ScreenType screenType, ManageDisplay* display) {
    m_ignoreButtons = true;
    m_currentScreen = screenType;
    m_param = PARAM1;
    if (m_currentScreen == BLUETOOTH_ERROR) {m_param = PARAMOK; /*display->setEnableATmode(NA);*/}
    if (m_currentScreen == USB_SETTINGS) {m_param = PARAM3;}
    display->setRadioSelected (m_param);
    display->setDisplayScreen(m_currentScreen);
}

void ManageState::screenIntro(ManageDisplay* display) {
    if (millis() - m_previousMillis >= TIME1) {
        screenTransition(ScreenType::CONTROL, display);
        m_previousMillis = millis();
    }
}

void ManageState::screenControl(ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeUART* uart) {

    //Serial.println("screenControl");

    if (m_button.btnCenterPress) {
        screenTransition(ScreenType::SELECT_MODE, display);
        radio->stopRadio();
        uart->stopBluetooth();
    }

    switch (m_currentMode) {
        case ModeType::MANUAL:    modeManual(move); break;
        case ModeType::UART:      modeUART(move, uart); break;
        case ModeType::RECORD:    modeRecord(move); break;
        case ModeType::REPLAY:    modeReplay(move); break;
        case ModeType::USBSERIAL: 
            modeUSB(move); 
            if (m_roleUART == TX) {
                uart->startBluetooth(m_bluetoothSet, m_roleUART);
                uart->setUARTMessage(m_messageEncode); 
            }
            break;
        case ModeType::BLUETOOTH: modeBluetooth(move, uart); break;
        case ModeType::RADIO:     
            modeRadio(move, radio); 
            if (m_roleUART == TX) {
                uart->startBluetooth(m_bluetoothSet, m_roleUART);
                if (m_radioSet.role == TX){ 
                    uart->setUARTMessage(m_messageEncode); 
                } else if (m_radioSet.role == RX) {
                    uart->setUARTMessage(m_messageDecode); 
                }
            }
            break;
    }
}


void ManageState::screenSelectMode(ManageDisplay* display, ManageMove* move, ModeUART* bluetooth) {
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
            screenTransition(ScreenType::CONTROL, display);
        } else if (m_currentMode == RADIO) {
            screenTransition(ScreenType::RADIO_SETTINGS, display);
        } else if (m_currentMode == UART) {
            screenTransition(ScreenType::UART_SETTINGS, display);
        } else if (m_currentMode == USBSERIAL) {
            screenTransition(ScreenType::USB_SETTINGS, display);
        } else if (m_currentMode == BLUETOOTH) {
            if (bluetooth->enableATmode() == OK) {
                screenTransition(ScreenType::BLUETOOTH_SETTINGS, display);
            } else if (bluetooth->enableATmode() == KO) {
                screenTransition(ScreenType::BLUETOOTH_ERROR, display);
            }
        } else {
            screenTransition(ScreenType::CONTROL, display);
        }
    }
    display->setModeSelected(m_currentMode);
}

void ManageState::screenATMode(ManageDisplay* display, ModeUART* bluetooth) {
    if (m_param == PARAMOK) {
        if (m_button.btnCenterClick) {
           screenTransition(ScreenType::SELECT_MODE, display);
        }
    }
}

void ManageState::screenBluetooth(ManageDisplay* display, ModeUART* bluetooth) {
    if (m_param == PARAM1) {
        if (m_button.btnRightPress) {
            if (m_bluetoothSet.code < 100) {
                m_bluetoothSet.code++;
            }
        } else if (m_button.btnLeftPress) {
            if (m_bluetoothSet.code > 1) {
                m_bluetoothSet.code--;
            }
        }
        display->setRadioKey (m_bluetoothSet.code);       
        if (m_button.btnCenterClick) {
            m_param = PARAM3;
            display->setRadioSelected (m_param);  
        }
    }  else if (m_param == PARAM3) {
        if (m_button.btnRightClick) {
            if (m_roleUART == TX){
                m_roleUART = NE;
            } else if (m_roleUART == NE) {
                m_roleUART = TX;
            }
            display->setRoleUART(m_roleUART);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAM1;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnCenterClick) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMOK) {
        if (m_button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            m_bluetoothSet.role = RX;
            bluetooth->startBluetooth(m_bluetoothSet, m_roleUART);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAMX;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnRightPress) {
            m_param = PARAM3;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMX) {
        if (m_button.btnCenterClick) {
           screenTransition(ScreenType::SELECT_MODE, display);
        }
        if (m_button.btnRightPress ) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    }
}

void ManageState::screenUSB(ManageDisplay* display, ModeUART* uart) {
    if (m_param == PARAM3) {
        if (m_button.btnRightClick) {
            if (m_roleUART == TX){
                m_roleUART = NE;
            } else if (m_roleUART == NE) {
                m_roleUART = TX;
            }
            display->setRoleUART(m_roleUART);
        }
        if (m_button.btnCenterClick) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMOK) {
        if (m_button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            uart->startBluetooth(m_bluetoothSet, m_roleUART);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAMX;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnRightPress) {
            m_param = PARAM3;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMX) {
        if (m_button.btnCenterClick) {
           screenTransition(ScreenType::SELECT_MODE, display);
        }
        if (m_button.btnRightPress ) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    }
}

void ManageState::screenUART(ManageDisplay* display, ModeUART* uart) {
    if (m_param == PARAM1) {
        if (m_button.btnRightClick) {
            if (m_bluetoothSet.role == TX){
                m_bluetoothSet.role = RX;
            } else if (m_bluetoothSet.role == RX) {
                m_bluetoothSet.role = TX;
            } else if (m_bluetoothSet.role == NE) {
                m_bluetoothSet.role = TX;
            }
            display->setTransmissionType(m_bluetoothSet.role);
        }
        if (m_button.btnCenterClick) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMOK) {
        if (m_button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            uart->startBluetooth(m_bluetoothSet, m_roleUART);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAMX;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnRightPress) {
            m_param = PARAM1;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMX) {
        if (m_button.btnCenterClick) {
           screenTransition(ScreenType::SELECT_MODE, display);
        }
        if (m_button.btnRightPress ) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    }
}

void ManageState::screenRadio(ManageDisplay* display, ModeRadio* radio) {
    if (m_param == PARAM1) {
        if (m_button.btnRightClick) {
            if (m_radioSet.role == TX){
                m_radioSet.role = RX;
            } else if (m_radioSet.role == RX) {
                m_radioSet.role = TX;
            }
            display->setTransmissionType(m_radioSet.role);
        }
        if (m_button.btnCenterClick) {
            m_param = PARAM2;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAM2) {
        if (m_button.btnRightPress) {
            if (m_radioSet.code < 10) {
                m_radioSet.code++;
            } else if (m_radioSet.code == 10) {
                m_radioSet.code = 1;
            }
        } 
        
        display->setRadioKey (m_radioSet.code);    

        if (m_button.btnLeftPress) {
            m_param = PARAM1;
            display->setRadioSelected (m_param);
        }
          
        if (m_button.btnCenterClick) {
            m_param = PARAM3;
            display->setRadioSelected (m_param);  
        }
    } else if (m_param == PARAM3) {
        if (m_button.btnRightClick) {
            if (m_roleUART == TX){
                m_roleUART = NE;
            } else if (m_roleUART == NE) {
                m_roleUART = TX;
            }
            display->setRoleUART(m_roleUART);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAM2;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnCenterClick) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMOK) {
        if (m_button.btnCenterClick) {
            display->setModeSelected(m_currentMode);
            screenTransition(ScreenType::CONTROL, display);
            radio->startRadio(m_radioSet);
        }
        if (m_button.btnLeftPress) {
            m_param = PARAMX;
            display->setRadioSelected (m_param);
        }
        if (m_button.btnRightPress) {
            m_param = PARAM3;
            display->setRadioSelected (m_param);
        }
    } else if (m_param == PARAMX) {
        if (m_button.btnCenterClick) {
           screenTransition(ScreenType::SELECT_MODE, display);
        }
        if (m_button.btnRightPress ) {
            m_param = PARAMOK;
            display->setRadioSelected (m_param);
        }
    }
}

void ManageState::modeManual(ManageMove* move) {  

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
        m_servoSet.pulse = 4;
        m_messageEncode.rotation = 20;
    } else if (m_button.btnRightPress) {
        m_servoSet.pulse = 8;
        m_messageEncode.rotation = 10;
    } 
    move->setServoSettings(m_servoSet);
}

void ManageState::modeRecord(ManageMove* move) {  
    modeManual(move);
}

void ManageState::modeReplay(ManageMove* move) {  
   // do {
    if (m_button.btnCenterPress) {
        move->eraseMovement();
    } else {
        move->startReplay();
    }
   // } while (not m_button.btnCenterPress);
}

void ManageState::modeRadio(ManageMove* move, ModeRadio* radio) {  
    if (m_radioSet.role == TX){  
        m_messageEncode.rotation = 30;
        modeManual(move);        
        m_messageEncode.currentLed = m_servoSet.servoId;
        radio->setRadioEncode(m_messageEncode);
    } else if (m_radioSet.role == RX) {
        m_messageDecode = radio->getRadioDecode();
        decodeMessage(move,&m_messageDecode); 
    }
}

void ManageState::modeUSB(ManageMove* move) {
    static char command[4];   // 2 chars + '\n' + '\0'
    static uint8_t index = 0;

    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\n') {
            command[index] = '\0';  // terminer la chaîne

            if (index >= 2) {       // au moins 2 caractères valides
                m_servoSet.servoId = command[0] - '1';
                char direction = command[1];

                m_messageEncode.currentLed = m_servoSet.servoId;
                move->setCurrentLED(m_servoSet.servoId);

                if (direction == 'L') {
                    m_servoSet.pulse = 4; 
                    m_messageEncode.rotation = 20;
                } else if (direction == 'R') {
                    m_servoSet.pulse = 8; 
                    m_messageEncode.rotation = 10;
                } else {
                    m_servoSet.pulse = 0; 
                    m_messageEncode.rotation = 30;
                } 
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

void ManageState::decodeMessage(ManageMove* move, PedroMessage* messageDecode) {  
    move->setCurrentLED(messageDecode->currentLed);
    m_servoSet.pulse = 0;
    m_servoSet.servoId = messageDecode->currentLed; 
    if (messageDecode->rotation == 20) {
        m_servoSet.pulse = 4;
    } else if (messageDecode->rotation == 10) {
        m_servoSet.pulse = 8;
    } 
    move->setServoSettings(m_servoSet);
}

void ManageState::modeBluetooth(ManageMove* move, ModeUART* bluetooth) {  
    m_messageDecode = bluetooth->getUARTMessage();
    decodeMessage(move,&m_messageDecode); 
    if (m_roleUART == TX) {
        bluetooth->setUARTMessage(m_messageDecode);
    }
}

void ManageState::modeUART(ManageMove* move, ModeUART* uart) {  
    if (m_bluetoothSet.role == TX){  
        m_messageEncode.rotation = 30;
        modeManual(move);        
        m_messageEncode.currentLed = m_servoSet.servoId;
        uart->setUARTMessage(m_messageEncode);
    } else if (m_bluetoothSet.role == RX) {
        m_messageDecode = uart->getUARTMessage();
        decodeMessage(move,&m_messageDecode);
    }
}

