#include "SevSeg.h"

// Constructors
SevSeg::SevSeg( byte a, byte b, byte c, byte d, byte e, byte f, byte g, boolean _commonAnode ) {
    commonAnode = _commonAnode;
    shiftRegister = false;

    pinArray = new byte[7];
    pinArray[0] = a;
    pinArray[1] = b;
    pinArray[2] = c;
    pinArray[3] = d;
    pinArray[4] = e;
    pinArray[5] = f;
    pinArray[6] = g;
    
    for (byte set=0; set<7; set++){
        pinMode(pinArray[set],OUTPUT);
    }
}

SevSeg::SevSeg( byte clock, byte latch, byte data, boolean _commonAnode, byte _numberOfDisplays) {
    commonAnode = _commonAnode;
    shiftRegister = true;
    numberOfDisplays = _numberOfDisplays < 1 ? 1 : _numberOfDisplays;
    
    pinArray = new byte[3];
    pinArray[0] = clock;
    pinArray[1] = latch;
    pinArray[2] = data;
    
    for (byte set=0; set<3; set++) {
        pinMode(pinArray[set],OUTPUT);
    }

}

void SevSeg::number(int number, const bool zeros, const byte base) {
    // Only shift register is allowed
	if (!shiftRegister) {
        return;
    }
            
    digitalWrite(pinArray[1], LOW);
    for (byte c = 0; c < numberOfDisplays; c++) {
        // Prints the units of number
        shiftOut(pinArray[2], pinArray[0], MSBFIRST, commonAnode ? ~dataArray[number % base] : dataArray[number % base]);  
        
        // Shifts right (in base 10)
        number /= base;
        
        // Note: first zero is printed
        if (number == 0) {
            for (byte k = c; k < numberOfDisplays; k++) {
                shiftOut(pinArray[2], pinArray[0], MSBFIRST, zeros ? dataArray[0] : (commonAnode ? 0xFF : 0x00) );
            }
            
            break;
        }
    }
    digitalWrite(pinArray[1], HIGH);
}


// Print a Hexadecimal number
void SevSeg::numberHex(byte hexNum)
{
	this->number(hexNum, 16);
}

// Print custom byte
void SevSeg::print(byte seq)
{
	if (!shiftRegister)
	{
        for (byte c = 0; c < 7; c++, seq >>= 1)
            digitalWrite(pinArray[c], commonAnode ? !(seq & 0x01) : seq & 0x01);
    }
    else
    {
		digitalWrite(pinArray[latchPin], LOW);
		shiftOut(pinArray[dataPin], pinArray[clockPin], MSBFIRST, commonAnode ? ~seq : seq);
		digitalWrite(latchPin, HIGH);
	}
}

// Turn off the displays
void SevSeg:clear()
{
	if (!shiftRegister)
	{
		for (byte c = 0; c < 7; c++)
            digitalWrite(pinArray[c], commonAnode ? HIGH : LOW);
	}
	else
	{
		for (byte c = 0; c < numberOfDisplays; c++)
			shiftOut(pinArray[dataPin], pinArray[clockPin], MSBFIRST, commonAnode ? 0xFF : 0x00);
	}
}

// Deallocates the dynamic data
SevSeg::~SevSeg() {
    delete[] pinArray;
}
