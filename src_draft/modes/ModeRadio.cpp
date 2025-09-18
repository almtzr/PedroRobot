#include "ModeRadio.h"

void ModeRadio::Init(RF24* radio) {
    m_radio = radio;
}

void ModeRadio::startTx(const byte* address) {
    if (!m_radio) return;
    m_radio->stopListening();
    m_radio->openWritingPipe(address);
}

void ModeRadio::startRx(const byte* address) {
    if (!m_radio) return;
    m_radio->openReadingPipe(1, address);
    m_radio->startListening();
}

void ModeRadio::stop() {
    if (!m_radio) return;
    m_radio->stopListening();
    m_radio->powerDown();
}
