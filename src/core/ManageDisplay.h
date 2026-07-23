#ifndef MANAGE_DISPLAY_H
#define MANAGE_DISPLAY_H

#include <Arduino.h>
#include "config/Config.h"

class ManageDisplay {
  public:
    void init();
    void screenIntro();
    void update();
    void screenControl();
    void screenSettings();
    void screenSelectMode();
    void oledControl();
    void oledRecord();
    void oledRepeat();
    void oledRadio();
    void oledUSB();
    void oledUART();
    void oledBluetooth();
    void oledTransmissionType ();
    void oledRadioKey ();
    void oledUpdate ();
    void oledCancel ();
    void oledBluetoothName ();
    void oledButtonOK ();
    void setDisplayScreen(ScreenType screen);
    void menuPosition(ModeType modeSelected, uint8_t positionX, uint8_t positionY, uint8_t bloc);
    void setRadioSelected(SetParam param);
    void setModeSelected(ModeType mode);
    void setTransmissionType(TransmissionType type);
    void setRadioKey(uint8_t key);
    void setEnableATmode(EnableATmode ATmode);
    char* modeToString(ModeType mode);

  private:
    EnableATmode m_enableATmode;
    ScreenType m_currentScreen;
    ModeType m_selectedMode;
    SetParam m_param;
    TransmissionSettings m_radioSet;
};

#endif
