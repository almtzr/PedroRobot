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
class ManageMove;
class ModeRadio;

class ManageState {
  public:
    ManageState();
    void updateState(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio);

  private:
    void screenIntro(ManageDisplay* display);
    void screenControl(Button button, ManageDisplay* display, ManageMove* move, ModeRadio* radio);
    void screenSelectMode(Button button, ManageDisplay* display);
    void screenRadio(Button button, ManageDisplay* display, ModeRadio* radio);
    bool allButtonsReleased(ManageButton* btn);
    void screenTransition(ScreenType screenType, ManageDisplay* display);
    void modeNormal(Button button, ManageMove* move);
    void modeRecord(Button button, ManageMove* move);
    void modeReplay(Button button, ManageMove* move);
    void modeRadio(Button button, ManageMove* move, ModeRadio* radio);
    void modeWebctrl(Button button, ManageMove* move);
    void modeBluetooth(Button button, ManageMove* move);

    Button m_button;
    ScreenType m_currentScreen;
    ModeType m_currentMode;
    unsigned long m_previousMillis;
    unsigned long m_intervalIntro;

    uint8_t m_selectMode, m_servoId;
    uint8_t m_selectRadio;
    bool m_btnCenterLongPress, m_btnLeft, m_btnRight, m_ignoreButtons;
    RadioSettings m_radioSet;
    RadioMessage m_radioEncode;
    RadioMessage m_radioDecode;
    ServoSettings m_servoSet;

};

#endif
