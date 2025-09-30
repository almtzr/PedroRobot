#include "ManageButton.h"

struct BtnState {
    bool on = false;
    bool click = false;
    bool press = false;
    unsigned long lastPressTime = 0;
};

BtnState btnCenter, btnRight, btnLeft;

void ManageButton::init() {
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_CENTER, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
}

static void updateButton(BtnState &btn, bool state, unsigned long now, bool longPress = false) {
    if (state) {
        if (!btn.on) {
            btn.on = true;
            btn.lastPressTime = now;
        }
        if (!btn.press && longPress) {
            if ((now - btn.lastPressTime) > TIME1) {
                btn.press = true;
            }
        } else {
            btn.press = true; // boutons sans gestion de "long press"
        }
    } else {
        btn.click = btn.on;
        btn.on = false;
        btn.press = false;
    }
}

void ManageButton::update() {
    unsigned long now = millis();

    updateButton(btnCenter, digitalRead(BTN_CENTER), now, true);
    updateButton(btnRight, digitalRead(BTN_RIGHT), now);
    updateButton(btnLeft,  digitalRead(BTN_LEFT), now);
}

// ======= Getters optimisés =======
bool ManageButton::getBtnCenterON() const    { return btnCenter.on; }
bool ManageButton::getBtnCenterClick() const { return btnCenter.click; }
bool ManageButton::getBtnCenterPress() const { return btnCenter.press; }

bool ManageButton::getBtnRightON() const     { return btnRight.on; }
bool ManageButton::getBtnRightClick() const  { return btnRight.click; }
bool ManageButton::getBtnRightPress() const  { return btnRight.press; }

bool ManageButton::getBtnLeftON() const      { return btnLeft.on; }
bool ManageButton::getBtnLeftClick() const   { return btnLeft.click; }
bool ManageButton::getBtnLeftPress() const   { return btnLeft.press; }
