#include "ModeRadio.h"
#include "core/ManageMove.h"

byte address[5] = {'P','E','D','R','1'};
RF24 radio(4, 12);

unsigned long lastSend = 0;

ManageMove* move;

ModeRadio::ModeRadio() {
  m_radioActive = false;
  m_radioSet.radioCode = 1;
  m_radioSet.TxRxType = TransmissionType::TX;
  m_messageEncode.currentLed = 0;
  m_messageEncode.rotation = 0;
  m_messageDecode.currentLed = 0;
  m_messageDecode.rotation = 0;
}

void ModeRadio::init() {  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);  //RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(120); //2400 + 120 = 2520MHz 76 default
}

void ModeRadio::startRadio(TransmissionSettings radioSet) {
    m_radioSet = radioSet;
    m_radioActive = true;
    initRadio();
}

void ModeRadio::setRadioEncode(PedroMessage radioMsg) {
    m_messageEncode = radioMsg;
}

PedroMessage ModeRadio::getRadioDecode() {
    return m_messageDecode;
}

void ModeRadio::initRadio() {
    address[4] = m_radioSet.radioCode;
    if (m_radioSet.TxRxType == TX) {
        radio.powerUp();
        radio.stopListening();
        radio.openWritingPipe(address);
    } else if (m_radioSet.TxRxType == RX) {
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
    if (m_radioSet.TxRxType == TX) {
        if (millis() - lastSend >= TIME2) {
            lastSend = millis();
            radio.write(&m_messageEncode, sizeof(m_messageEncode));
        }
    } else if (m_radioSet.TxRxType == RX) {
        if (radio.available()) {
            radio.read(&m_messageDecode, sizeof(m_messageDecode));
        }
    }
}