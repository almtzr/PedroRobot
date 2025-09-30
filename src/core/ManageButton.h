#ifndef __MANAGEBUTTON_H__
#define __MANAGEBUTTON_H__

#include <Arduino.h>
#include "config/Config.h"

class ManageButton {
  public:
    void init();
    void update();

    bool getBtnCenterON() const;
    bool getBtnCenterClick() const;
    bool getBtnCenterPress() const;

    bool getBtnRightON() const;
    bool getBtnRightClick() const;
    bool getBtnRightPress() const;

    bool getBtnLeftON() const;
    bool getBtnLeftClick() const;
    bool getBtnLeftPress() const;

    void setBtnCenterON(bool state);
    void setBtnCenterClick(bool state);
    void setBtnCenterPress(bool state);

  private:
    bool m_btnRightON;
    bool m_btnRightClick;
    bool m_btnRightPress;
    bool m_btnLeftON;
    bool m_btnLeftClick;
    bool m_btnLeftPress;
    bool m_btnCenterON;
    bool m_btnCenterClick;
    bool m_btnCenterPress;

    unsigned long m_lastCenterPressTime;
};

#endif
