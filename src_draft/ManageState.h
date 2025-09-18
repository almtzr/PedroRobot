#ifndef __MANAGESTATE_H__
#define __MANAGESTATE_H__

#include <Arduino.h>
#include "Command.h"

class ManageButton;
class ManageDisplay;

enum class Screen : uint8_t {
    INTRO,
    CONTROL,
    SELECT_MODE,
    RADIO
};

class ManageState {
  public:
    ManageState();

    void Init();
    void updateState(ManageButton* btn, ManageDisplay* display);

    Screen getCurrentScreen() const { return m_currentScreen; }
    Command getCommand() const { return m_cmd; }

  private:
    void screenIntro();
    void screenControl(ManageButton* btn, ManageDisplay* display);
    void screenSelectMode(ManageButton* btn, ManageDisplay* display);
    void screenRadio();

    Screen m_currentScreen;
    Command m_cmd;
    unsigned long m_previousMillis;
    unsigned long m_intervalIntro;

    uint8_t m_selectMode;
    uint8_t m_selectRadio;
    uint8_t m_radioKey;
    bool m_btnCenterLongPress, m_btnLeft, m_btnRight;

};

#endif
