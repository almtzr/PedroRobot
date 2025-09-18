#ifndef MANAGE_DISPLAY_H
#define MANAGE_DISPLAY_H

#include <Arduino.h>

// Types d’écran
enum ScreenType {
    SCREEN_INTRO,
    SCREEN_CONTROL,
    SCREEN_SELECT_MODE,
    SCREEN_RADIO,
    SCREEN_SETTINGS
};

enum ModeType {
    MODE_NORMAL,
    MODE_RECORD,
    MODE_REPLAY,
    MODE_RADIO,
    MODE_WEB,
    MODE_BLUETOOTH
};

class ManageDisplay {
  public:
    void Init();
    void setDisplayScreen(ScreenType screen);
    ScreenType getScreen() const;

    void setModeActivated(const char* mode);
    void setModeSelected(ModeType mode);
    void setRadioType(uint8_t type);
    void setRadioSelected(uint8_t select);
    void setRadioKey(uint8_t key);

  private:
    ScreenType m_currentScreen;
    ModeType m_selectedMode;
    uint8_t m_radioType;
    uint8_t m_radioSelect;
    uint8_t m_radioKey;
};

#endif
