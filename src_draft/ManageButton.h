#ifndef __MANAGEBUTTON_H__
#define __MANAGEBUTTON_H__

#include <Arduino.h>
#include "config/Config.h"

class ManageButton {
  public:
    void Init();
    void update();

    bool getBtnLeftState() const;
    bool getBtnRightState() const;
    bool getBtnCenterPressed() const;
    bool getBtnCenterReleased() const;
    bool getBtnCenterLongPress() const;

    void setBtnCenterPressed(bool state);
    void setBtnCenterReleased(bool state);
    void setBtnCenterLongPress(bool state);

  private:
    bool m_btnLeft;
    bool m_btnRight;
    bool m_btnCenterPressed;
    bool m_btnCenterReleased;
    bool m_btnCenterLongPress;

    unsigned long m_lastCenterPressTime;
};

#endif
