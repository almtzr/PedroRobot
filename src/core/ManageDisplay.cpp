#include "U8glib.h"
#include "ManageDisplay.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
constexpr uint8_t SCREEN_SIZE_X = 128;
constexpr uint8_t SCREEN_SIZE_Y = 64;

void ManageDisplay::init() {
    m_currentScreen = INTRO;
    m_selectedMode = MANUAL;
    m_param = PARAM1;
    m_enableATmode = NA;
    m_radioSet.code = 1;
    m_radioSet.role = TX;
    m_roleUART = NE;
    screenIntro();
}

char* ManageDisplay::modeToString(ModeType mode) {
   /// static char radioMode[16];
    switch (mode) {
        case MANUAL:   return "MANUAL";
        case RECORD:   return "RECORD";
        case UART:
        if (m_currentScreen == CONTROL){
            if (m_radioSet.role == TX) {
                snprintf(buffer, sizeof(buffer), "UART TX");
            } else {
                snprintf(buffer, sizeof(buffer), "UART RX");
            }
            return buffer;
        } else {
            return "UART";
        } 
        case REPLAY:   return "REPLAY";
        case RADIO:
        if (m_currentScreen == CONTROL){
            if (m_radioSet.role == TX) {
                snprintf(buffer, sizeof(buffer), "RADIO TX %d", m_radioSet.code);
            } else {
                snprintf(buffer, sizeof(buffer), "RADIO RX %d", m_radioSet.code);
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
        case ScreenType::UART_SETTINGS:     screenSettings(); break;
        case ScreenType::USB_SETTINGS:     screenSettings(); break;
        case ScreenType::BLUETOOTH_SETTINGS: screenSettings(); break;
        case ScreenType::BLUETOOTH_ERROR: screenSettings(); break;
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
        u8g.drawStr(2, SCREEN_SIZE_Y/2.3, "MODE");
        u8g.setFont(u8g_font_fub14r);
        u8g.drawStr(2, SCREEN_SIZE_Y/1.3, modeToString(m_selectedMode));
        
        if (m_roleUART == TX){
            u8g.setFont(u8g_font_8x13B);
            u8g.drawStr(SCREEN_SIZE_X/2 + 42, SCREEN_SIZE_Y/2.3, "TX");
        } else if (m_roleUART == RX){
            u8g.setFont(u8g_font_8x13B);
            u8g.drawStr(SCREEN_SIZE_X/2 + 42, SCREEN_SIZE_Y/2.3, "RX");
        }
        if (m_selectedMode == BLUETOOTH){
            sprintf(buffer, "PEDROROBOT%d", m_radioSet.code);
            u8g.setFont(u8g_font_7x13B);
            u8g.drawStr(2, SCREEN_SIZE_Y - 2, "NAME:");
            u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y - 2, buffer);
        }
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
           u8g.drawStr(2, SCREEN_SIZE_Y/2.3, "ROLE:");
           u8g.drawStr(2, SCREEN_SIZE_Y/1.6, "CODE:");
           u8g.drawStr(2, SCREEN_SIZE_Y/1.2, "UART:");
           oledTransmissionRole();
           oledRadioKey();
           oledCancel();
           oledUARTRole();
        } else if (m_currentScreen == BLUETOOTH_SETTINGS) { 
           u8g.drawStr(2, 13, TITLE_BLUETOOTH);
           u8g.drawStr(2, SCREEN_SIZE_Y/2.3, "NAME:");
           u8g.drawStr(2, SCREEN_SIZE_Y/1.2, "UART:");
           oledBluetoothName();
           oledUARTRole();
           oledCancel();
        } else if (m_currentScreen == USB_SETTINGS) { 
           u8g.drawStr(2, 13, TITLE_USB);
           u8g.drawStr(2, SCREEN_SIZE_Y/1.2, "UART:");
           oledUARTRole();
           oledCancel();
        } else if (m_currentScreen == BLUETOOTH_ERROR) { 
           u8g.drawStr(2, 13, TITLE_BLUETOOTH_ERROR);
           u8g.drawStr(10, SCREEN_SIZE_Y/2, "AT MODE DISABLE");
        } else if (m_currentScreen == UART_SETTINGS) { 
           u8g.drawStr(2, 13, TITLE_UART);
           u8g.drawStr(2, SCREEN_SIZE_Y/2.3, "ROLE:");
           oledTransmissionRole();
           oledCancel();
        }
        oledButtonOK();
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::oledTransmissionRole() {  

    u8g.setFont(u8g_font_7x13B);

    if (m_param == PARAM1) {
        u8g.drawBox(SCREEN_SIZE_X/3.3, SCREEN_SIZE_Y/2.3 - 10, SCREEN_SIZE_X/2 + 20, 12);
        u8g.setColorIndex(1);
    } else {
        u8g.setColorIndex(0);
    }
    if (m_radioSet.role == TX) {
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/2.3, TYPE_TX);
    } else if (m_radioSet.role == RX){
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/2.3, TYPE_RX);
    }
}

void ManageDisplay::oledUARTRole() {  

    u8g.setFont(u8g_font_7x13B);

    if (m_param == PARAM3) {
        u8g.drawBox(SCREEN_SIZE_X/3.3, SCREEN_SIZE_Y/1.2 - 10, SCREEN_SIZE_X/6, 12);
        u8g.setColorIndex(1);
    } else {
        u8g.setColorIndex(0);
    }
    if (m_roleUART == TX) {
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/1.2, "TX");
    } else if (m_roleUART == RX){
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/1.2, "RX");
    } else if (m_roleUART == NE){
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/1.2, "NE");
    }
}

void ManageDisplay::oledRadioKey() {  

    u8g.setFont(u8g_font_7x13B);

    sprintf(buffer, "%d", m_radioSet.code);
    
    if (m_param == PARAM2) {
        u8g.drawBox(SCREEN_SIZE_X/3.3, SCREEN_SIZE_Y/1.6 - 10, SCREEN_SIZE_X/6, 12);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/1.6, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/1.6, buffer);
    }
}

void ManageDisplay::oledBluetoothName() {  

    u8g.setFont(u8g_font_7x13B);

    sprintf(buffer, "PEDROROBOT%d", m_radioSet.code);
    
    if (m_param == PARAM1) {
        u8g.drawBox(SCREEN_SIZE_X/3.3, SCREEN_SIZE_Y/2.3 - 10, SCREEN_SIZE_X/2 + 24, 12);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/2.3, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3.3 + 2, SCREEN_SIZE_Y/2.3, buffer);
    }
}

void ManageDisplay::oledCancel() {  
    
    u8g.setFont(u8g_font_7x13B);
    if (m_param == PARAMX) {
        u8g.drawBox(SCREEN_SIZE_X/2 - 7, SCREEN_SIZE_Y - 14, SCREEN_SIZE_X/6, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/2, SCREEN_SIZE_Y - 2, "X");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/2, SCREEN_SIZE_Y - 2, "X");
    }
}

void ManageDisplay::oledUpdate() {  
    
    u8g.setFont(u8g_font_7x13B);
    if (m_param == PARAMUPDATE) {
        u8g.drawBox(1, SCREEN_SIZE_Y - 14, SCREEN_SIZE_X/2.4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(4, SCREEN_SIZE_Y - 2, "UPDATE");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(4, SCREEN_SIZE_Y - 2, "UPDATE");
    }
}

void ManageDisplay::oledButtonOK() {  
    
    u8g.setFont(u8g_font_7x13B);
    if (m_param == PARAMOK) {
        u8g.drawBox(SCREEN_SIZE_X/2 + 36, SCREEN_SIZE_Y - 14, SCREEN_SIZE_X/4.8, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/2 + 42, SCREEN_SIZE_Y - 2, "OK");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/2 + 42, SCREEN_SIZE_Y - 2, "OK");
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

void ManageDisplay::oledUART() {  
    menuPosition (UART,90,3,SCREEN_SIZE_X/3.3);
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
        oledUART();
        u8g.setColorIndex(1);

    } while( u8g.nextPage() );
}

void ManageDisplay::setRadioSelected(SetParam param) { m_param = param; }

void ManageDisplay::setEnableATmode(EnableATmode ATmode) { m_enableATmode = ATmode; }

void ManageDisplay::setModeSelected(ModeType mode) {
    m_selectedMode = mode;
}

void ManageDisplay::setTransmissionType(TransmissionType type) {
    m_radioSet.role = type;
}

void ManageDisplay::setRoleUART(TransmissionType type) {
    m_roleUART = type;
}

void ManageDisplay::setRadioKey(uint8_t key) {
    m_radioSet.code = key;
}
