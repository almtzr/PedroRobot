#include "U8glib.h"
#include "ManageDisplay.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

void ManageDisplay::init() {
    m_currentScreen = INTRO;
    m_selectedMode = MANUAL;
    m_param = PARAM1;
    m_enableATmode = NA;
    m_radioSet.radioCode = 1;
    m_radioSet.radioType = TX;
    screenIntro();
}

char* ManageDisplay::modeToString(ModeType mode) {
   /// static char radioMode[16];
    switch (mode) {
        case MANUAL:   return "MANUAL";
        case RECORD:   return "RECORD";
        case REPLAY:   return "REPLAY";
        case RADIO:
        if (m_currentScreen == CONTROL){
            if (m_radioSet.radioType == TX) {
                snprintf(buffer, sizeof(buffer), "RADIO TX %d", m_radioSet.radioCode);
            } else {
                snprintf(buffer, sizeof(buffer), "RADIO RX %d", m_radioSet.radioCode);
            }
            return buffer;
        } else {
            return "RADIO";
        }  
        case USBSERIAL:  return "USB SERIAL";
        case BLUETOOTH:return "BLUETOOTH";
        default:       return "UNKNOWN";
    }
}

void ManageDisplay::setDisplayScreen(ScreenType screen) {
    m_currentScreen = screen;
}

void ManageDisplay::update() {
    switch (m_currentScreen) {
        case ScreenType::INTRO:              screenIntro(); break;
        case ScreenType::CONTROL:            screenControl(); break;
        case ScreenType::SELECT_MODE:        screenSelectMode(); break;
        case ScreenType::RADIO_SETTINGS:     screenSettings(); break;
        case ScreenType::BLUETOOTH_SETTINGS: screenSettings(); break;
        case ScreenType::BLUETOOTH_UPDATE: screenSettings(); break;
    }
}

void ManageDisplay::screenIntro() {  
    u8g.firstPage();
    do { 
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(SCREEN_SIZE_X/6, SCREEN_SIZE_Y/2, TITLE_DLE);
        u8g.setFont(u8g_font_6x13B);
        u8g.drawStr(SCREEN_SIZE_X/1.6, SCREEN_SIZE_Y/1.4, RELEASE);
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::screenControl() {  
    u8g.firstPage();
    do {   
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(SCREEN_SIZE_X/6, 13, TITLE_DLE);
        
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, SCREEN_SIZE_Y/2, "MODE");
        u8g.setFont(u8g_font_fub14r);
        u8g.drawStr(2, SCREEN_SIZE_Y - 10, modeToString(m_selectedMode));
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
    m_currentScreen = -1;
}

void ManageDisplay::menuPosition(ModeType selectedMode, uint8_t positionX, uint8_t positionY, uint8_t bloc) {  
    if (m_selectedMode == selectedMode) {
        u8g.drawBox(positionX - 2, LEVELWIDTH + (positionY - 1)*16, bloc, 14);
        u8g.setColorIndex(1);
        u8g.drawStr(positionX, SCREEN_SIZE_Y/4.4*2 + (positionY - 1)*16, modeToString(selectedMode));
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(positionX, SCREEN_SIZE_Y/4.4*2 + (positionY - 1)*16, modeToString(selectedMode));
    }
}

void ManageDisplay::screenSettings() {
    u8g.firstPage();
    do {  
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_7x13B);
        if (m_currentScreen == RADIO_SETTINGS) { 
           u8g.drawStr(2, 13, TITLE_RADIO);
           u8g.drawStr(2, SCREEN_SIZE_Y/2, "TYPE:");
           u8g.drawStr(2, SCREEN_SIZE_Y/1.3,"CODE:");
           oledRadioType();
           oledRadioKey();
        } else if (m_currentScreen == BLUETOOTH_SETTINGS) { 
           u8g.drawStr(2, 13, TITLE_BLUETOOTH);
           if (m_enableATmode == KO) u8g.drawStr(10, SCREEN_SIZE_Y/2, "AT MODE DISABLE");
           oledUpdate();
        } else if (m_currentScreen == BLUETOOTH_UPDATE) { 
           u8g.drawStr(2, 13, TITLE_BLUETOOTH_UPDATE);
           u8g.drawStr(2, SCREEN_SIZE_Y/2, "NAME:");
           oledBluetoothName();
        }
        
        oledRadioOK();
        
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::oledRadioType() {  

    u8g.setFont(u8g_font_7x13B);

    if (m_param == PARAM1) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/2 - 12, SCREEN_SIZE_X/2 + 20, 15);
        u8g.setColorIndex(1);
    } else {
        u8g.setColorIndex(0);
    }
    if (m_radioSet.radioType == TX) {
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/2, TYPE_TX);
    } else if (m_radioSet.radioType == RX){
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/2, TYPE_RX);
    }
}

void ManageDisplay::oledRadioKey() {  

    u8g.setFont(u8g_font_7x13B);

    sprintf(buffer, "%d", m_radioSet.radioCode);
    
    if (m_param == PARAM2) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/1.3 - 12, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/1.3, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/1.3, buffer);
    }
}

void ManageDisplay::oledBluetoothName() {  

    u8g.setFont(u8g_font_7x13B);

    sprintf(buffer, "PEDROROBOT%d", m_radioSet.radioCode);
    
    if (m_param == PARAM1) {
        u8g.drawBox(SCREEN_SIZE_X/3 - 5, SCREEN_SIZE_Y/2 - 12, SCREEN_SIZE_X/2 + 24, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3 - 1, SCREEN_SIZE_Y/2, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3 - 1, SCREEN_SIZE_Y/2, buffer);
    }
}

void ManageDisplay::oledUpdate() {  
    
    u8g.setFont(u8g_font_8x13B);
    if (m_param == PARAM4) {
        u8g.drawBox(2, SCREEN_SIZE_Y - 18, SCREEN_SIZE_X/2, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(7, SCREEN_SIZE_Y - 5, "UPDATE");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(7, SCREEN_SIZE_Y - 5, "UPDATE");
    }
}

void ManageDisplay::oledRadioOK() {  
    
    u8g.setFont(u8g_font_8x13B);
    if (m_param == PARAM3) {
        u8g.drawBox(SCREEN_SIZE_X/2 + 25, SCREEN_SIZE_Y - 18, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/2 + 34, SCREEN_SIZE_Y - 5, "OK");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/2 + 34, SCREEN_SIZE_Y - 5, "OK");
    }
}

void ManageDisplay::oledControl() {  
    menuPosition (MANUAL,3,1,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRecord() {  
    menuPosition (RECORD,3,2,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRepeat() {  
    menuPosition (REPLAY,3,3,SCREEN_SIZE_X/2.8); 
}

void ManageDisplay::oledUSB() {  
    menuPosition (USBSERIAL,50,1,SCREEN_SIZE_X/1.8); 
}

void ManageDisplay::oledBluetooth() {  
    menuPosition (BLUETOOTH,50,2,SCREEN_SIZE_X/1.9); 
}

void ManageDisplay::oledRadio() {  
    menuPosition (RADIO,50,3,SCREEN_SIZE_X/3.3); 
}

void ManageDisplay::screenSelectMode() {  
    u8g.firstPage();
    do {  
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, SCREEN_SIZE_Y/4.5, TITLE_MODE);

        u8g.setFont(u8g_font_7x13B);
        oledControl();
        oledRecord();
        oledRepeat();
        oledUSB();
        oledBluetooth();
        oledRadio();
        u8g.setColorIndex(1);

    } while( u8g.nextPage() );
}

void ManageDisplay::setRadioSelected(SetParam param) { m_param = param; }

void ManageDisplay::setEnableATmode(EnableATmode ATmode) { m_enableATmode = ATmode; }

void ManageDisplay::setModeSelected(ModeType mode) {
    m_selectedMode = mode;
}

void ManageDisplay::setRadioType(RadioType type) {
    m_radioSet.radioType = type;
}

void ManageDisplay::setRadioKey(uint8_t key) {
    m_radioSet.radioCode = key;
}
