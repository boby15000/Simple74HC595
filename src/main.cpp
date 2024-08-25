#include <Arduino.h>
#include <Simple74HC595.h>
#include <Tempo.h>

Simple74HC595 hc(12,13,11);
Tempo tpo;

void setup() {
  tpo.Start(10, tpo.Seconde);
  hc.SetAll(false);
}

void loop() {
  
  hc.Set(2, true);
  delay(1000);
  hc.Set(2, false);
  delay(1000);

  if ( tpo.End() ) {
    hc.Set(4, true);
    tpo.Start();
  } 

}

