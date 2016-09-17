/*
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                                Diagnostics.ino                                                                |
  |                                                               SPIFlash library                                                                |
  |                                                                   v 2.4.0                                                                     |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                                    Marzogh                                                                    |
  |                                                                  11.09.2016                                                                   |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
  |                                                                                                                                               |
  |                                  For a full diagnostics rundown - with error codes and details of the errors                                  |
  |                                uncomment #define RUNDIAGNOSTIC in SPIFlash.cpp in the library before compiling                                |
  |                                             and loading this application onto your Arduino.                                                   |
  |                                                                                                                                               |
  |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

#include<SPIFlash.h>
#include<SPI.h>

//#if defined (ARDUINO_ARCH_SAMD)
#define _debug SerialUSB
//#else
//#define _debug Serial
//#endif

#define WINBOND     0xEF
#define MICROCHIP   0xBF

char printBuffer[128];

SPIFlash flash;

void setup() {
  _debug.begin(115200);
  _debug.print(F("Initialising Flash memory"));
  for (int i = 0; i < 10; ++i)
  {
    _debug.print(F("."));
  }
  _debug.println();
  flash.begin();
  _debug.println();
  _debug.println();

  randomSeed(analogRead(A0));
  getID();
  diagnose();
}

void loop() {

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_debug Print Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void clearprintBuffer()
{
  for (uint8_t i = 0; i < 128; i++) {
    printBuffer[i] = 0;
  }
}

void printLine() {
  _debug.println(F("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
}

void printPass() {
  _debug.print(F("Pass"));
}

void printFail() {
  _debug.print(F("Fail"));
}

void printTab(uint8_t a, uint8_t b) {
  for (uint8_t i = 0; i < a; i++) {
    _debug.print(F("\t"));
  }
  if (b > 0) {
    _debug.print("||");
    for (uint8_t i = 0; i < b; i++) {
      _debug.print(F("\t"));
    }
  }
}

void printTime(uint32_t _wTime, uint32_t _rTime) {
  printTab(2, 1);
  printTimer(_wTime);
  printTab(2, 1);
  printTimer(_rTime);
}

void printTimer(uint32_t _us) {

  if (_us > 1000000) {
    float _s = _us / (float)1000000;
    _debug.print(_s, 4);
    _debug.print(" s");
  }
  else if (_us > 10000) {
    float _ms = _us / (float)1000;
    _debug.print(_ms, 4);
    _debug.print(" ms");
  }
  else {
    _debug.print(_us);
    _debug.print(F(" us"));
  }
}
