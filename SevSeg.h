/* Seven Segmen Driver Library v1.0
 * 
 * Adapted by
 * Giulio Fieramosca
 *    http://www.glgprograms.it
 * 
 * Originally written by
 * Alexander Brevig
 *    http://alexanderbrevig.github.io/
 * 
*/

#ifndef SevSeg_h
#define SevSeg_h

#define COMMON_CATHODE false
#define COMMON_ANODE true

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Array of bits corresponding to digits 0-9
// from left to right => segment g to segment a
const byte dataArray[] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

class SevSeg {

public:
  // Direct-wiring constructor
  SevSeg (byte a, byte b, byte c, byte d, byte e, byte f, byte g, boolean _commonAnode = false );
  // ShiftRegister-wiring constructor
  SevSeg (byte data, byte latch, byte clock, boolean _commonAnode = false, byte _numberOfDisplays = 1);
  
  ~SevSeg();
  
  void print(byte number);
  void print(int number, bool zeros = true);
    
private:
  
  // Pointer to the pins' array
  byte *pinArray;
  
  byte numberOfDisplays;
  
  boolean shiftRegister;
  boolean commonAnode;
};

#endif
