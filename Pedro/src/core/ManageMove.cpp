#include "ManageMove.h"
#include <Servo.h>

Servo servoList[4];
const uint8_t ledPins[4] = {13, 11, 8, 7};
const uint8_t servoPins[4] = {5, 6, 9, 10}; 
int16_t pulse;
// servoSpeed => Can be adjusted based on your Pedro Robot's movement. 
// Higher values result in faster movement, lower values result in slower movement.
const int servoSpeed[4] = {-200, -220, 200, 150};
////////////

ManageMove::ManageMove() {
    m_currentLED = 0;
}

void ManageMove::Init() {
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
    
   /* Serial.print("LEDId ");
    Serial.print(LEDId);
    Serial.print(" m_currentLED ");
    Serial.println(m_currentLED);*/
    digitalWrite(ledPins[m_currentLED], LOW);
    digitalWrite(ledPins[LEDId], HIGH);
    m_currentLED = LEDId;
}

void ManageMove::servoIDLE(uint8_t servoId) {
    servoList[servoId].writeMicroseconds(1500);
}

void ManageMove::rotationLeft(uint8_t servoId) {
    pulse = 1500 - servoSpeed[servoId];
    servoList[servoId].writeMicroseconds(pulse);
}

void ManageMove::rotationRight(uint8_t servoId) {
    pulse = 1500 + servoSpeed[servoId];
    servoList[servoId].writeMicroseconds(pulse);
}

void ManageMove::AddMovement(int pulse, unsigned long duration, uint8_t servo) {
    if (m_index < MAX_MOVEMENTS) {
        m_movements[m_index++] = {pulse, duration, servo};
    }
}

void ManageMove::Replay() {
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
