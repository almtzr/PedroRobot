#include "ModeBluetooth.h"

ModeBluetooth::ModeBluetooth() {
  m_bluetoothActive = false;
  m_enableATmode = NA;
  m_radioDecode.currentLed = 0;
  m_radioDecode.rotation = 0;
}

void ModeBluetooth::stopBluetooth() {
    m_bluetoothActive = false;
}

void ModeBluetooth::startBluetooth(RadioSettings radioSet) {
    m_radioSet = radioSet;
    m_bluetoothActive = true;

    if (m_enableATmode == OK) {
        //Serial.println("AT NAME DONE");
        sprintf(buffer, "AT+NAME=PEDROROBOT%d", m_radioSet.radioCode);
        Serial1.println(buffer);
        delay(500);
    }
}

EnableATmode ModeBluetooth::enableATmode() {
    // Envoie commande "AT"
    Serial1.println("AT");
    delay(500);

    // Lecture réponse dans buffer
    idx = 0;
    while (Serial1.available() && idx < sizeof(buffer) - 1) {
        buffer[idx++] = Serial1.read();
    }
    buffer[idx] = '\0'; // fin de chaîne

    for (uint8_t i = 0; i < idx; i++) {
        if (buffer[i] == '\r' || buffer[i] == '\n') {
        buffer[i] = '\0';
        break;
        }
    }
    // Vérification
    if (strcmp(buffer, "OK") == 0) {
        //Serial.println(F("HC-05 en mode AT (réponse OK)"));
        m_enableATmode = OK;
    } else {
        //Serial.print(F("Pas en mode AT ou mauvaise vitesse. Réponse = "));
        if (idx > 0) Serial.println(buffer);
        else Serial.println(F("aucune"));
        m_enableATmode = KO;
    }
    return m_enableATmode;
}

RadioMessage ModeBluetooth::getRadioDecode() {
    return m_radioDecode;
}

void ModeBluetooth::update() {
    if (!m_bluetoothActive) return;
    while (Serial1.available()) {
        char c = Serial1.read();
        m_radioDecode.rotation = 30;
        if (c == '\n') {
            bufferBT[idx] = '\0'; // fin de chaîne
            idx = 0;

            // décodage des 2 chiffres
            uint8_t cmd = bufferBT[0] - '0';  // ex: '1' -> 1

       //     Serial.println(bufferBT[0]);

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
