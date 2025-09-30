#include "ManageMove.h"
#include <Servo.h>

Servo servoList[4];
const uint8_t ledPins[4] = {13, 11, 8, 7};
const uint8_t servoPins[4] = {5, 6, 9, 10}; 
int16_t pulse;
const int servoSpeed[4] = {-200, -220, 200, 150};
////////////

ManageMove::ManageMove() {
    m_currentLED = 0;
    m_lastPulse = 1500;
    m_previousMillis = 0;
    m_startRecord = false;
    m_servoSet.pulse = 0;
    m_servoSet.servoId = 0;
}

void ManageMove::init() {
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_CENTER, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    for (uint8_t i = 0; i < 4; i++) {
       pinMode(ledPins[i], OUTPUT);
       digitalWrite(ledPins[i], LOW);
       servoList[i].attach(servoPins[i]);
    }
    digitalWrite(ledPins[m_currentLED], HIGH);
}

void ManageMove::LEDOFF() {
    for (uint8_t i = 0; i < 4; i++) {
       digitalWrite(ledPins[i], LOW);
    }
}

void ManageMove::setCurrentLED(uint8_t LEDId) {
    digitalWrite(ledPins[m_currentLED], LOW);
    digitalWrite(ledPins[LEDId], HIGH);
    m_currentLED = LEDId;
}

void ManageMove::servoIDLE(uint8_t servoId) {
    servoList[servoId].writeMicroseconds(1500);
}

void ManageMove::setServoSettings(ServoSettings servoSet) {
    m_servoSet = servoSet;
}

void ManageMove::initRecord() {
    m_index = 0;
    m_previousMillis = millis();
    m_startRecord = true;
}

void ManageMove::startRecord() {
    if (abs(pulse - m_lastPulse) > 5) {
        unsigned long now = millis();
        if (m_index < MAX_MOVEMENTS) {
            m_movements[m_index++] = {m_lastPulse, now - m_previousMillis, m_servoSet.servoId};
        }
        m_previousMillis = now;
        m_lastPulse = pulse;
    }
}

void ManageMove::update() {
    
    if (m_servoSet.pulse == 4){
        pulse = 1500 - servoSpeed[m_servoSet.servoId];  
    } else if (m_servoSet.pulse == 8){
        pulse = 1500 + servoSpeed[m_servoSet.servoId];  
    } else {
        pulse = 1500;
    }

    if (m_startRecord) {
        startRecord();
    }

    servoList[m_servoSet.servoId].writeMicroseconds(pulse);
}

void ManageMove::eraseMovement() {
    for (uint8_t i = 0; i < MAX_MOVEMENTS; i++) {
        m_movements[i].pulse = 0;
        m_movements[i].duration = 0;
        m_movements[i].servo = 0;
    }   
}

void ManageMove::startReplay() {
    
    // Serial.println("startReplay..");
    // Mettre tous les servos à neutre avant de commencer
    for (uint8_t i = 0; i < 4; i++) {
      servoList[i].writeMicroseconds(1500);
      digitalWrite(ledPins[i], LOW);
    }
  
    // Lecture séquentielle des mouvements
    for (uint8_t i = 0; i < m_index; i++) {
      uint8_t currentServo = m_movements[i].servo;
  
      // Activer uniquement le servo concerné
      for (uint8_t j = 0; j < 4; j++) {
        if (j == currentServo) {
          digitalWrite(ledPins[j], HIGH); // Allumer la LED correspondante
        } else {
          digitalWrite(ledPins[j], LOW);  // Éteindre les autres
          servoList[j].writeMicroseconds(1500); // Stopper les autres servos
        }
      }
  
      // Exécuter le mouvement
      servoList[currentServo].writeMicroseconds(m_movements[i].pulse);
      delay(m_movements[i].duration);
  
      // Remettre le servo à neutre après le mouvement
      servoList[currentServo].writeMicroseconds(1500);
    }
  
    // Éteindre toutes les LEDs à la fin
    for (uint8_t i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
      servoList[i].writeMicroseconds(1500);
    }
}

