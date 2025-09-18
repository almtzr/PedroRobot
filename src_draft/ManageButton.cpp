#include "ManageButton.h"

void ManageButton::Init() {
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_CENTER, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);

    m_btnLeft = false;
    m_btnRight = false;
    m_btnCenterPressed = false;
    m_btnCenterReleased = false;
    m_btnCenterLongPress = false;
    m_lastCenterPressTime = 0;
}

void ManageButton::update() {
    // Lecture des boutons
    m_btnLeft = digitalRead(BTN_LEFT);
    m_btnRight = digitalRead(BTN_RIGHT);

    bool centerState = digitalRead(BTN_CENTER);
    unsigned long now = millis();

    if (centerState) {
            Serial.println("Center: ");

        if (!m_btnCenterPressed) {
            m_btnCenterPressed = true;
            m_lastCenterPressTime = now;
        }
        if ((now - m_lastCenterPressTime) > 3000) {

            Serial.println("Button Long: ");
            m_btnCenterLongPress = true;
        }
    } else {
        if (m_btnCenterPressed) {
            m_btnCenterReleased = true;
        }
        m_btnCenterPressed = false;
        m_btnCenterLongPress = false;
    }
}

// Getters
bool ManageButton::getBtnLeftState() const { return m_btnLeft; }
bool ManageButton::getBtnRightState() const { return m_btnRight; }
bool ManageButton::getBtnCenterPressed() const { return m_btnCenterPressed; }
bool ManageButton::getBtnCenterReleased() const { return m_btnCenterReleased; }
bool ManageButton::getBtnCenterLongPress() const { return m_btnCenterLongPress; }

// Setters
void ManageButton::setBtnCenterPressed(bool state) { m_btnCenterPressed = state; }
void ManageButton::setBtnCenterReleased(bool state) { m_btnCenterReleased = state; }
void ManageButton::setBtnCenterLongPress(bool state) { m_btnCenterLongPress = state; }
