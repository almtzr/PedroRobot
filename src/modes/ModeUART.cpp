#include "ModeUART.h"

ModeUART::ModeUART() {
  m_bluetoothActive = false;
  m_enableATmode = NA;
  m_messageDecode.currentLed = 0;
  m_messageDecode.rotation = 0;
}

void ModeUART::stopBluetooth() {
    m_bluetoothActive = false;
}

void ModeUART::startBluetooth(TransmissionSettings bluetoothSet, TransmissionType roleUART) {
    m_uartSet = bluetoothSet;
    m_roleUART = roleUART;
    m_bluetoothActive = true;

    if (m_enableATmode == OK) {
        //Serial.println("AT NAME DONE");
        sprintf(buffer, "AT+NAME=PEDROROBOT%d", m_uartSet.code);
        Serial1.println(buffer);
        delay(500);
    }
    
}

EnableATmode ModeUART::enableATmode() {
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

void ModeUART::setUARTMessage(PedroMessage uartMsg) {
    m_messageEncode = uartMsg;
}

PedroMessage ModeUART::getUARTMessage() {
    return m_messageDecode;
}

void ModeUART::update() {
    if (!m_bluetoothActive) return;

    if (m_uartSet.role == TX or m_roleUART == TX) {
        // Envoi du numéro de LED (1 à 4)
        Serial1.write('1' + m_messageEncode.currentLed);
        Serial1.write('\n');

        // Envoi de la rotation
        switch (m_messageEncode.rotation) {
            case 10:
                Serial1.write('5');
                break;

            case 20:
                Serial1.write('6');
                break;

            case 30:
                Serial1.write('7');
                break;
        }

        Serial1.write('\n');    
    } 
    
    if (m_uartSet.role == RX or m_roleUART == RX) {
        if (Serial1.available()) {
            char cmd = Serial1.read();

            // Serial.print("Reçu : ");
            // Serial.println(cmd);

            switch(cmd) {
                case '1':
                case '2':
                case '3':
                case '4':
                    m_messageDecode.currentLed = cmd - '1';
                    break;

                case '5':
                    m_messageDecode.rotation = 10;
                    break;

                case '6':
                    m_messageDecode.rotation = 20;
                    break;

                case '7':
                    m_messageDecode.rotation = 30;
                    break;
            }
        }
    }
}
