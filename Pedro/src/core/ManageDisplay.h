#ifndef MANAGE_DISPLAY_H
#define MANAGE_DISPLAY_H

#include <Arduino.h>
#include "config/Config.h"

class ManageDisplay {
  public:
    void Init();
    void screenIntro();
    void updateDisplay();
    void screenControl();
    void screenRadio();
    void screenSelectMode();
    void oledControl();
    void oledRecord();
    void oledRepeat();
    void oledRadio();
    void oledWebControl();
    void oledBluetooth();
    void oledRadioType ();
    void oledRadioKey ();
    void oledRadioOK ();
    void setDisplayScreen(ScreenType screen);
    ScreenType getScreen() const;
    void menuPosition(ModeType modeSelected, uint8_t positionX, uint8_t positionY, uint8_t bloc);
    void setRadioSelected(uint8_t selectRadio);
    void setModeActivated(const char* mode);
    void setModeSelected(ModeType mode);
    void setRadioType(RadioType type);
    void setRadioKey(uint8_t key);
    char* modeToString(ModeType mode);

  private:
    ScreenType m_currentScreen;
    ModeType m_selectedMode;
    uint8_t m_radioSelect,  m_selectRadio;
    RadioSettings m_radioSet;
};

#endif
