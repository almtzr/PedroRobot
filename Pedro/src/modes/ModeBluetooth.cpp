#include "ModeBluetooth.h"

void ModeBluetooth::init() {
    // Init Bluetooth (Serial, HC-05, etc.)
}

ModeBluetooth::ModeBluetooth() {
  m_bleutoothActive = false;
  m_radioDecode.currentLed = 0;
  m_radioDecode.rotation = 0;
}

void ModeBluetooth::stopBluetooth() {
    m_bleutoothActive = false;
}

void ModeBluetooth::startBluetooth() {
    m_bleutoothActive = true;
}

RadioMessage ModeBluetooth::getRadioDecode() {
    return m_radioDecode;
}

void ModeBluetooth::update() {
    if (!m_bleutoothActive) return;
    while (Serial1.available()) {
        char c = Serial1.read();
        m_radioDecode.rotation = 30;
        if (c == '\n') {
            bufferBT[idx] = '\0'; // fin de chaîne
            idx = 0;

            // décodage des 2 chiffres
            uint8_t cmd = bufferBT[0] - '0';  // ex: '1' -> 1

            Serial.println(bufferBT[0]);

            if (cmd >= 1 && cmd <= 4) {
                m_radioDecode.currentLed = cmd - 1;
            }

            switch (cmd) {
                case 5: m_radioDecode.rotation = 10; break;
                case 6: m_radioDecode.rotation = 20; break;
                case 7: m_radioDecode.rotation = 30; break;
                //default: rotation = 0; break;

            }

        } else if (idx < 2) {
            bufferBT[idx++] = c;  // enregistrer chiffre si valide
        } else {
            idx = 0; // reset en cas d'erreur
        }
    }
}
