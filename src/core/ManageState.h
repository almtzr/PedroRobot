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
class ModeUART;

class ManageState {
  public:
    ManageState();
    void update(ManageButton* btn, ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeUART* uart);
    void screenIntro(ManageDisplay* display);
    void screenControl(ManageDisplay* display, ManageMove* move, ModeRadio* radio, ModeUART* uart);
    void screenSelectMode(ManageDisplay* display, ManageMove* move, ModeUART* bluetooth);
    void screenRadio(ManageDisplay* display, ModeRadio* radio);
    void screenUART(ManageDisplay* display, ModeUART* uart);
    void screenUSB(ManageDisplay* display, ModeUART* uart);
    void screenBluetooth(ManageDisplay* display, ModeUART* bluetooth);
    void screenATMode(ManageDisplay* display, ModeUART* bluetooth);
   // void screenUpdateBluetooth(ManageDisplay* display, ModeUART* bluetooth);
    bool allButtonsReleased(ManageButton* btn);
    void screenTransition(ScreenType screenType, ManageDisplay* display);
    void modeManual(ManageMove* move);
    void modeRecord(ManageMove* move);
    void modeReplay(ManageMove* move);
    void modeRadio(ManageMove* move, ModeRadio* radio);
    void modeUSB(ManageMove* move);
    void modeBluetooth(ManageMove* move, ModeUART* bluetooth);
    void modeUART(ManageMove* move, ModeUART* uart);
    void decodeMessage(ManageMove* move, PedroMessage* messageDecode);
  private:
    Button m_button;
    ScreenType m_currentScreen;
    ModeType m_currentMode;
    SetParam m_param;
    unsigned long m_previousMillis;

    bool m_ignoreButtons;
    TransmissionSettings m_radioSet;
    TransmissionSettings m_bluetoothSet;
    TransmissionType m_roleUART;
    PedroMessage m_messageEncode;
    PedroMessage m_messageDecode;
    ServoSettings m_servoSet;

};

#endif
