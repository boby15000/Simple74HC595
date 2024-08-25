#ifndef Simple74HC595_h
#include "Simple74HC595.h"
#endif

/**
 * Constructeur
 * @pin_sensor : entrée analogique du capteur
 * @sensibilite : sensibilité du capteur
 * @type_sensibilite : Type de la sensibilité AMPERE_PAR_VOLT ou MILLIVOLT_PAR_AMPERE
 * @frequence : fréquence du réseau mesuré (par défaut 50hz)
 * @tension : tension du réseau mesuré (par défaut 230V)
*/
Simple74HC595::Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre){
    pinMode(pin_DS, OUTPUT);
    pinMode(pin_STCP, OUTPUT);
    pinMode(pin_SHCP, OUTPUT);
    this->_pin_DS = pin_DS;
    this->_pin_STCP = pin_STCP;
    this->_pin_SHCP = pin_SHCP;
    this->_NbrPins = min(max(numberRegistre,1),10)*8;
    this->clearRegisters();
    this->RefreshRegister();
}


void Simple74HC595::clearRegisters(){
  for(int i = this->_NbrPins - 1; i >=  0; i--){
     this->_registers[i] = LOW;
  }
} 



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



void Simple74HC595::Set(byte pin, boolean etat){
    this->_registers[pin] = etat;
    this->RefreshRegister();
}


void Simple74HC595::SetAll(boolean etat){
    for(int i = this->_NbrPins - 1; i >=  0; i--){
        this->_registers[i] = etat;
    }
    this->RefreshRegister();
}