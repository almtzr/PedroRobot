#ifndef __MANAGESTATE_H__
#define __MANAGESTATE_H__

#include <Arduino.h>
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
class ModeBluetooth;

class ManageState {
  public:
    ManageState();
    void update(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeBluetooth* bluetooth);
    void screenIntro(ManageDisplay* display);
    void screenControl(ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeBluetooth* bluetooth);
    void screenSelectMode(ManageDisplay* display, ManageMove* move);
    void screenRadio(ManageDisplay* display, ModeRadio* radio);
    void screenBluetooth(ManageDisplay* display, ModeBluetooth* bluetooth);
    void screenUpdateBluetooth(ManageDisplay* display, ModeBluetooth* bluetooth);
    bool allButtonsReleased(ManageButton* btn);
    void screenTransition(ScreenType screenType, ManageDisplay* display);
    void modeManual(ManageMove* move);
    void modeRecord(ManageMove* move);
    void modeReplay(ManageMove* move);
    void modeRadio(ManageMove* move, ModeRadio* radio);
    void modeUSB(ManageMove* move);
    void modeBluetooth(ManageMove* move, ModeBluetooth* bluetooth);
  private:
    Button m_button;
    ScreenType m_currentScreen;
    ModeType m_currentMode;
    SetParam m_param;
    unsigned long m_previousMillis;

    bool m_ignoreButtons;
    RadioSettings m_radioSet;
    RadioMessage m_radioEncode;
    RadioMessage m_radioDecode;
    ServoSettings m_servoSet;

};

#endif
