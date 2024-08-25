#include <Arduino.h>
#include <Simple74HC595.h>
#include <Tempo.h>

Simple74HC595 hc(12,13,11);
Tempo tpo1, tpo2;

void setup() {
  tpo1.Start(10, tpo1.Seconde);
  tpo2.Init(5, tpo2.Seconde);
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
  /*
  if ( !tpo2.End() )
  {
    hc.Set(2, true);
    delay(250);
    hc.Set(2, false);
    delay(250);
  }


  if ( tpo1.End() ) {
    hc.Set(4, true);
    tpo2.Start();
  }


  if ( tpo2.End() ) {
    hc.Set(0, true);
    delay(1000);
    hc.Set(0, false);
    delay(1000);
    tpo1.Start();
  } 
  */
}

