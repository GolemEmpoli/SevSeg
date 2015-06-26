/* Seven Segment Driver Library v1.0
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

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define COMMON_CATHODE false
#define COMMON_ANODE true

#define clockPin 0
#define latchPin 1
#define dataPin 2


// Array of bits corresponding to digits 0-9
// from left to right => segment g to segment a
const byte dataArray[] = {
    0b00111111,		// 0
    0b00000110,		// 1
    0b01011011,		// 2
    0b01001111,		// 3
    0b01100110,		// 4
    0b01101101,		// 5
    0b01111101,		// 6
    0b00000111,		// 7
    0b01111111,		// 8
    0b01101111,		// 9
    0b01110111,		// A (10)
    0b01111100,		// b (11)
    0b00111001,		// C (12)
    0b01011110,		// d (13)
    0b01111001, 	// E (14)
    0b01110001,		// F (15)
    0b10000000		// Dot Point (16)
};

class SevSeg {

public:
  // Direct-wiring constructor
  SevSeg (byte a, byte b, byte c, byte d, byte e, byte f, byte g, boolean _commonAnode = false );
  // ShiftRegister-wiring constructor
  SevSeg (byte data, byte latch, byte clock, boolean _commonAnode = false, byte _numberOfDisplays = 1);
  
  ~SevSeg();
  
  void number(int number, const bool zeros = true, const base = 10);
  void numberHex(byte hexNum);
  void print(byte seq);			// Print a byte sequence
  void clear();				// Turn off all the displays
    
private:
  
  // Pointer to the pins' array
  byte *pinArray;
  
  byte numberOfDisplays;
  
  boolean shiftRegister;
  boolean commonAnode;
};

#endif
