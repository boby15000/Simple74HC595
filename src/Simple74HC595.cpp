#ifndef Simple74HC595_h
  #include "Simple74HC595.h"
#endif

/**
 * Constructeur
 * @pin_DS        : broche DS  (pin 14 du 74HC595)
 * @pin_STCP      : broche STCP / latch (pin 12 du 74HC595)
 * @pin_SHCP      : broche SHCP / clock (pin 11 du 74HC595)
 * @numberRegistre : nombre de registres en daisy-chain (1 à 10)
 */
Simple74HC595::Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre) {
    this->_pin_DS      = pin_DS;
    this->_pin_STCP    = pin_STCP;
    this->_pin_SHCP    = pin_SHCP;
    this->_NbrRegistres = min(max(numberRegistre, (byte)1), (byte)10);

    pinMode(this->_pin_DS,   OUTPUT);
    pinMode(this->_pin_STCP, OUTPUT);
    pinMode(this->_pin_SHCP, OUTPUT);

    this->SetAll(false);
}

/**
 * Lit l'état d'un bit dans le tableau _registers
 */
boolean Simple74HC595::_getBit(byte pin) {
    return (_registers[pin / 8] >> (pin % 8)) & 0x01;
}

/**
 * Écrit l'état d'un bit dans le tableau _registers (sans appliquer)
 */
void Simple74HC595::_setBit(byte pin, boolean etat) {
    if (etat)
        _registers[pin / 8] |=  (1 << (pin % 8));
    else
        _registers[pin / 8] &= ~(1 << (pin % 8));
}

/**
 * Applique les états stockés vers les 74HC595
 */
void Simple74HC595::RefreshRegister() {
    byte totalPins = this->_NbrRegistres * 8;

    digitalWrite(this->_pin_STCP, LOW);

    for (int i = totalPins - 1; i >= 0; i--) {
        digitalWrite(this->_pin_SHCP, LOW);
        digitalWrite(this->_pin_DS, this->_getBit(i));
        digitalWrite(this->_pin_SHCP, HIGH);
    }

    digitalWrite(this->_pin_STCP, HIGH);
}

/**
 * Définit l'état d'une sortie sans appliquer
 */
void Simple74HC595::SetNoUpdate(byte pin, boolean etat) {
    if (pin >= this->_NbrRegistres * 8) return;
    this->_setBit(pin, etat);
}

/**
 * Définit l'état de toutes les sorties sans appliquer
 */
void Simple74HC595::SetAllNoUpdate(boolean etat) {
    for (int i = 0; i < this->_NbrRegistres; i++) {
        _registers[i] = etat ? 0xFF : 0x00;
    }
}

/**
 * Définit l'état d'une sortie et applique
 */
void Simple74HC595::Set(byte pin, boolean etat) {
    if (pin >= this->_NbrRegistres * 8) return;
    this->_setBit(pin, etat);
    this->RefreshRegister();
}

/**
 * Définit l'état de toutes les sorties et applique
 */
void Simple74HC595::SetAll(boolean etat) {
    this->SetAllNoUpdate(etat);
    this->RefreshRegister();
}

/**
 * Inverse l'état d'une sortie et applique
 */
void Simple74HC595::Toggle(byte pin) {
    if (pin >= this->_NbrRegistres * 8) return;
    this->_setBit(pin, !this->_getBit(pin));
    this->RefreshRegister();
}
