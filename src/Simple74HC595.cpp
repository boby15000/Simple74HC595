#ifndef Simple74HC595_h
#include "Simple74HC595.h"
#endif

/**
 * Constructeur
 * @pin_DS : pin d'entrée DS (correspond au pin 14 du 74HC595)
 * @pin_STCP : pin d'entrée SHCP (correspond au pin 12 du 74HC595)
 * @pin_SHCP : pin d'entrée SHCP (correspond au pin 11 du 74HC595)
 * @numberRegistre : nombre de registre à décalage (par défaut 1 , maximum 10)
*/
Simple74HC595::Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre){
    pinMode(pin_DS, OUTPUT);
    pinMode(pin_STCP, OUTPUT);
    pinMode(pin_SHCP, OUTPUT);
    this->_pin_DS = pin_DS;
    this->_pin_STCP = pin_STCP;
    this->_pin_SHCP = pin_SHCP;
    this->_NbrPins = min(max(numberRegistre,1),10)*8;
    this->SetAll(false);
}

/*
 * Applique les Etats au Entrées/Sorties 
*/
void Simple74HC595::RefreshRegister(){
  // Tant que LOW les modifications ne seront pas affectés
  digitalWrite(this->_pin_STCP, LOW);

  // boucle pour affecter chaque pin des 74hc595
  for(int i = this->_NbrPins - 1; i >=  0; i--){

    //doit etre a l'etat bas pour changer de colonne plus tard
    digitalWrite(this->_pin_SHCP, LOW);

    //affecte la valeur sur le pin DS correspondant a un pin du 74hc595
    digitalWrite(this->_pin_DS, this->_registers[i]);
    
    //colonne suivante
    digitalWrite(this->_pin_SHCP, HIGH);

  }
  //applique toutes les valeurs au 74hc595
  digitalWrite(this->_pin_STCP, HIGH);
}

/*
 * Détermine l'état de la sortie précisé en paramétre sans validation 
*/
void Simple74HC595::SetNoUpdate(byte pin, boolean etat){
    this->_registers[pin] = etat;
}


/*
 * Détermine l'état de toutes les sorties sans validation 
*/
void Simple74HC595::SetAllNoUpdate(boolean etat){
    for(int i = this->_NbrPins - 1; i >=  0; i--){
        this->_registers[i] = etat;
    }
}

/*
 * Détermine l'état de la sortie précisé en paramétre avec validation 
*/
void Simple74HC595::Set(byte pin, boolean etat){
    this->_registers[pin] = etat;
    this->RefreshRegister();
}

/*
 * Détermine l'état de toutes les sorties avec validation 
*/
void Simple74HC595::SetAll(boolean etat){
    for(int i = this->_NbrPins - 1; i >=  0; i--){
        this->_registers[i] = etat;
    }
    this->RefreshRegister();
}