#if ARDUINO >= 100    
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef Simple74HC595_INCLUDED
#define Simple74HC595_INCLUDED

/**
 * Bibliothèque pour simplifier l'utilisation des registres à décalage 74HC595.
 * Supporte jusqu'à 10 registres en daisy-chain.
 * Optimisation mémoire : 1 octet par registre (vs 8 sans masquage).
 */
class Simple74HC595
{
  public:
    Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre = 1);
    void Set(byte pin, boolean etat);          // Définit l'état d'une sortie et applique
    void SetAll(boolean etat);                 // Définit l'état de toutes les sorties et applique
    void SetNoUpdate(byte pin, boolean etat);  // Définit l'état d'une sortie sans appliquer
    void SetAllNoUpdate(boolean etat);         // Définit l'état de toutes les sorties sans appliquer
    void Toggle(byte pin);                     // Inverse l'état d'une sortie et applique
    void RefreshRegister();                    // Applique les états au 74HC595

  private:
    byte _pin_DS;
    byte _pin_STCP;
    byte _pin_SHCP;
    byte _NbrRegistres;   // Nombre de registres (1–10)
    uint8_t _registers[10]; // 1 bit par sortie, 1 octet par registre
    
    boolean _getBit(byte pin);
    void _setBit(byte pin, boolean etat);
};

#endif
