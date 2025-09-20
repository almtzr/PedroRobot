#ifndef __MANAGESTATE_H__
#define __MANAGESTATE_H__

#include <Arduino.h>
#include "Command.h"
#include "config/Config.h"

struct Button {
  bool btnRightClick;
  bool btnLeftClick;
  bool btnCenterClick;
  bool btnRightPress;
  bool btnLeftPress;
  bool btnCenterPress;
};


class ManageButton;
class ManageDisplay;



class ManageState {
  public:
    ManageState();

    void Init();
    void updateState(ManageButton* btn, ManageDisplay* display);
    Command getCommand() const { return m_cmd; }

  private:
    void screenIntro(ManageDisplay* display);
    void screenControl(Button button, ManageDisplay* display);
    void screenSelectMode(Button button, ManageDisplay* display);
    void screenRadio(Button button, ManageDisplay* display);
    bool allButtonsReleased(ManageButton* btn);
    void screenTransition(ScreenType screenType, ManageDisplay* display);
    void modeNormal(Button button);
    void modeRecord(Button button);
    void modeReplay(Button button);
    void modeRadio(Button button);
    void modeWebctrl(Button button);
    void modeBluetooth(Button button);

    Button m_button;
    ScreenType m_currentScreen;
    ModeType m_currentMode;
    Command m_cmd;
    unsigned long m_previousMillis;
    unsigned long m_intervalIntro;

    uint8_t m_selectMode;
    uint8_t m_selectRadio;
    uint8_t m_radioKey, m_radioType;
    bool m_btnCenterLongPress, m_btnLeft, m_btnRight, m_ignoreButtons;

};

#endif
