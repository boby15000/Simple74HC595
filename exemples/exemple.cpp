#include <Arduino.h>
#include <Simple74HC595.h>

Simple74HC595 hc(12,13,11);

void setup() {
  hc.SetAll(false);
}

void loop() {
  
    for (size_t i = 0; i < 8; i++)
    {
    hc.Set(i, true);
    delay(500);
    }

    delay(2500);

    for (size_t i = 0; i < 8; i++)
    {
    hc.Set(i, false);
    delay(500);
    }


    //hc.SetNoUpdate(1, false);
    //hc.SetNoUpdate(4, true);
    //hc.RefreshRegister();

    //hc.SetAllNoUpdate(false);
    //hc.RefreshRegister();


}