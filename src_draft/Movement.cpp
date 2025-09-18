#include "Movement.h"
#include <Servo.h>

extern Servo servoList[4];
extern const uint8_t ledPins[4];

void MovementManager::Init() {
    m_index = 0;
}

void MovementManager::StartRecord() {
    m_index = 0;
}

void MovementManager::AddMovement(int pulse, unsigned long duration, uint8_t servo) {
    if (m_index < MAX_MOVEMENTS) {
        m_movements[m_index++] = {pulse, duration, servo};
    }
}

void MovementManager::Replay() {
    for (uint8_t i = 0; i < m_index; i++) {
        uint8_t currentServo = m_movements[i].servo;

        for (uint8_t j = 0; j < 4; j++) {
            if (j == currentServo) {
                digitalWrite(ledPins[j], HIGH);
            } else {
                digitalWrite(ledPins[j], LOW);
                servoList[j].writeMicroseconds(1500);
            }
        }

        servoList[currentServo].writeMicroseconds(m_movements[i].pulse);
        delay(m_movements[i].duration);  // ⚠️ à remplacer par millis() si besoin
        servoList[currentServo].writeMicroseconds(1500);
    }

    for (uint8_t i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], LOW);
        servoList[i].writeMicroseconds(1500);
    }
}
