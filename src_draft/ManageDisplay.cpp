#include "U8glib.h"
#include "ManageDisplay.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

void ManageDisplay::Init() {
    m_currentScreen = INTRO;
    m_selectedMode = NORMAL;
    m_radioType = 1;
    m_radioKey = 1;
    m_selectRadio = 1;
    screenIntro();
    Serial.print("Mode sélectionné: ");
    Serial.println(m_selectedMode);
}

char* ManageDisplay::modeToString(ModeType mode) {
    static char radioMode[16];
    switch (mode) {
        case NORMAL:   return "NORMAL";
        case RECORD:   return "RECORD";
        case REPLAY:   return "REPLAY";
        case RADIO:
        if (m_currentScreen == CONTROL){
            if (m_radioType == 1) {
                snprintf(radioMode, sizeof(radioMode), "RADIO TX %d", m_radioKey);
            } else {
                snprintf(radioMode, sizeof(radioMode), "RADIO RX %d", m_radioKey);
            }
            return radioMode;
        } else {
            return "RADIO";
        }  
        case WEBCTRL:  return "WEBCTRL";
        case BLUETOOTH:return "BLUETOOTH";
        default:       return "UNKNOWN";
    }
}

void ManageDisplay::setDisplayScreen(ScreenType screen) {
    m_currentScreen = screen;
}

void ManageDisplay::updateDisplay() {
    switch (m_currentScreen) {
        case ScreenType::INTRO:       screenIntro(); break;
        case ScreenType::CONTROL:     screenControl(); break;
        case ScreenType::SELECT_MODE: screenSelectMode(); break;
        case ScreenType::RADIO_SETTINGS:       screenRadio(); break;
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

void ManageDisplay::screenRadio() {
    u8g.firstPage();
    do {  
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, 13, TITLE_RADIO);
        
        u8g.drawStr(2, SCREEN_SIZE_Y/2, "TYPE:");
        u8g.drawStr(2, SCREEN_SIZE_Y/1.3,"CODE:");

        oledRadioType();
        oledRadioKey();
        oledRadioOK();
        
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::oledRadioType() {  

    u8g.setFont(u8g_font_7x13B);

    if (m_selectRadio == 1) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/2 - 12, SCREEN_SIZE_X/2 + 20, 15);
        u8g.setColorIndex(1);
    } else {
        u8g.setColorIndex(0);
    }
    if (m_radioType == 1) {
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/2, TYPE_TX);
    } else  if (m_radioType == 2){
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/2, TYPE_RX);
    }
}

void ManageDisplay::oledRadioKey() {  

    u8g.setFont(u8g_font_7x13B);

    char buffer[4];
    sprintf(buffer, "%d", m_radioKey);
    
    if (m_selectRadio == 2) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/1.3 - 12, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/1.3, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3 + 2, SCREEN_SIZE_Y/1.3, buffer);
    }
}

void ManageDisplay::oledRadioOK() {  
    
    u8g.setFont(u8g_font_8x13B);
    if (m_selectRadio == 3) {
        u8g.drawBox(SCREEN_SIZE_X/2 + 15, SCREEN_SIZE_Y - 18, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/2 + 24, SCREEN_SIZE_Y - 5, "OK");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/2 + 24, SCREEN_SIZE_Y - 5, "OK");
    }
}

void ManageDisplay::oledControl() {  
    menuPosition (NORMAL,3,1,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRecord() {  
    menuPosition (RECORD,3,2,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRepeat() {  
    menuPosition (REPLAY,3,3,SCREEN_SIZE_X/2.8); 
}

void ManageDisplay::oledWebControl() {  
    menuPosition (WEBCTRL,50,1,SCREEN_SIZE_X/2.4); 
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
        oledWebControl();
        oledBluetooth();
        oledRadio();
        u8g.setColorIndex(1);

    } while( u8g.nextPage() );
}

void ManageDisplay::setRadioSelected(uint8_t selectRadio) { m_selectRadio = selectRadio; }


ScreenType ManageDisplay::getScreen() const {
    return m_currentScreen;
}

void ManageDisplay::setModeActivated(const char* mode) {
   // Serial.print("Mode activé: ");
   // Serial.println(mode);
}

void ManageDisplay::setModeSelected(ModeType mode) {
    m_selectedMode = mode;
    //Serial.print("Mode sélectionné: ");
    //Serial.println(mode);
}

void ManageDisplay::setRadioType(uint8_t type) {
    m_radioType = type;
   // Serial.print("Radio type: ");
   // Serial.println(type);
}

void ManageDisplay::setRadioKey(uint8_t key) {
    m_radioKey = key;
  //  Serial.print("Radio key: ");
  //  Serial.println(key);
}
