#include "ModeRadio.h"
#include "core/ManageMove.h"

byte address[5] = {'P','E','D','R','1'};
RF24 radio(4, 12);

unsigned long lastSend = 0;

ManageMove* move;

ModeRadio::ModeRadio() {
  m_radioActive = false;
  m_radioSet.radioCode = 1;
  m_radioSet.radioType = RadioType::TX;
  m_radioEncode.currentLed = 0;
  m_radioEncode.rotation = 0;
  m_radioDecode.currentLed = 0;
  m_radioDecode.rotation = 0;
}

void ModeRadio::init() {  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);  //RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(120); //2400 + 120 = 2520MHz 76 default
}

void ModeRadio::startRadio(RadioSettings radioSet) {
    m_radioSet = radioSet;
    m_radioActive = true;
    initRadio();
}

void ModeRadio::setRadioEncode(RadioMessage radioMsg) {
    m_radioEncode = radioMsg;
}

RadioMessage ModeRadio::getRadioDecode() {
    return m_radioDecode;
}

void ModeRadio::initRadio() {
    address[4] = m_radioSet.radioCode;
    if (m_radioSet.radioType == TX) {
        radio.powerUp();
        radio.stopListening();
        radio.openWritingPipe(address);
    } else if (m_radioSet.radioType == RX) {
        move->LEDOFF();
        radio.powerUp();
        radio.closeReadingPipe(1);
        radio.openReadingPipe(1, address);
        radio.startListening();
    }
}

void ModeRadio::stopRadio() {
    if (!m_radioActive) return;
    radio.stopListening();  // arrête RX et met en standby TX
    radio.flush_tx();       // vide le buffer d’émission
    radio.flush_rx();       // vide le buffer de réception
    radio.powerDown();      // OFF total
    m_radioActive = false;
}

void ModeRadio::update() {
    if (!m_radioActive) return;
    if (m_radioSet.radioType == TX) {
        if (millis() - lastSend >= TIME2) {
            lastSend = millis();
            radio.write(&m_radioEncode, sizeof(m_radioEncode));
        }
    } else if (m_radioSet.radioType == RX) {
        if (radio.available()) {
            radio.read(&m_radioDecode, sizeof(m_radioDecode));
        }
    }
}