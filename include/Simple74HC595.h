#if ARDUINO >= 100    
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef Simple74HC595_INCLUDED
#define Simple74HC595_INCLUDED

/*
  Permet de simplier l'utilisation des registres à décalage.
  Cette library est limité à 10 registres.
*/


class Simple74HC595
{
  public :

    Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre = 1);

    void Set(byte pin, boolean etat); // Défaut l'état de la Pin
    void SetAll(boolean etat); // Etat "Haut" ou "Bas" sur toutes les sorties
    void SetNoUpdate(byte pin, boolean etat);
    void SetAllNoUpdate(boolean etat);
    void RefreshRegister();

  private :
    int _pin_DS;
    int _pin_STCP;
    int _pin_SHCP;
    int _NbrPins;
    boolean _registers[80];
};

#endif