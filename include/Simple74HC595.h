#if ARDUINO >= 100    
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef Simple74HC595_INCLUDED
#define Simple74HC595_INCLUDED


class Simple74HC595
{
  public :

    Simple74HC595(byte pin_DS, byte pin_STCP, byte pin_SHCP, byte numberRegistre = 1);

    void Set(byte pin, boolean etat);
    void SetAll(boolean etat);

  private :
    int _pin_DS;
    int _pin_STCP;
    int _pin_SHCP;
    int _NbrPins;
    boolean _registers[80];
    void RefreshRegister();
    void clearRegisters(); 
};

#endif