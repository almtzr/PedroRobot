#include "ManageButton.h"

void ManageButton::init() {
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_CENTER, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);

    m_btnCenterON = false;
    m_btnCenterClick = false;
    m_btnCenterPress = false;
    m_lastCenterPressTime = 0;
}

void ManageButton::update() {
    // Lecture des boutons
    bool centerState = digitalRead(BTN_CENTER);
    bool rightState = digitalRead(BTN_RIGHT);
    bool leftState = digitalRead(BTN_LEFT);
    unsigned long now = millis();

    if (centerState) {
        if (!m_btnCenterON) {
            m_btnCenterON = true;
            m_lastCenterPressTime = now;
        }
        if (!m_btnCenterPress) {
            if ((now - m_lastCenterPressTime) > 3000) {
                m_btnCenterPress = true;
            }
        }
    } else {
        if (m_btnCenterON) {
            m_btnCenterClick = true;
        } else {
            m_btnCenterClick = false;
        }
        m_btnCenterON = false;
        m_btnCenterPress = false;
    }

    if (rightState) {
        if (!m_btnRightON) {
            m_btnRightON = true;
        }
        if (!m_btnRightPress) {
            m_btnRightPress = true;
        }
    } else {
        if (m_btnRightON) {
            m_btnRightClick = true;
        } else {
            m_btnRightClick = false;
        }
        m_btnRightON = false;
        m_btnRightPress = false;
    }

    if (leftState) {
        if (!m_btnLeftON) {
            m_btnLeftON = true;
        }
        if (!m_btnLeftPress) {
            m_btnLeftPress = true;
        }
    } else {
        if (m_btnLeftON) {
            m_btnLeftClick = true;
        } else {
            m_btnLeftClick = false;
        }
        m_btnLeftON = false;
        m_btnLeftPress = false;
    }
}

// Getters

bool ManageButton::getBtnCenterON() const { return m_btnCenterON; }
bool ManageButton::getBtnCenterClick() const { return m_btnCenterClick; }
bool ManageButton::getBtnCenterPress() const { return m_btnCenterPress; }

bool ManageButton::getBtnRightON() const { return m_btnRightON; }
bool ManageButton::getBtnRightClick() const { return m_btnRightClick; }
bool ManageButton::getBtnRightPress() const { return m_btnRightPress; }

bool ManageButton::getBtnLeftON() const { return m_btnLeftON; }
bool ManageButton::getBtnLeftClick() const { return m_btnLeftClick; }
bool ManageButton::getBtnLeftPress() const { return m_btnLeftPress; }

// Setters
void ManageButton::setBtnCenterON(bool state) { m_btnCenterON = state; }
void ManageButton::setBtnCenterClick(bool state) { m_btnCenterClick = state; }
void ManageButton::setBtnCenterPress(bool state) { m_btnCenterPress = state; }
