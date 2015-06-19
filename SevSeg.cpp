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
    numberOfDisplays = _numberOfDisplays;
    
    pinArray = new byte[3];
    pinArray[0] = clock;
    pinArray[1] = latch;
    pinArray[2] = data;
    
    for (byte set=0; set<3; set++){
        pinMode(pinArray[set],OUTPUT);
    }

}

// Prints a number on the display
void SevSeg::print(byte number) {
	if (!shiftRegister) {
        for (byte c = 0, dataTmp = dataArray[number]; c < 7; c++, dataTmp = dataTmp >> 1) {
            digitalWrite(pinArray[c], commonAnode ? !(dataTmp & 0x01) : dataTmp & 0x01);
        }
        
    }
    else {
        if (numberOfDisplays != 1) {
            digitalWrite(pinArray[1], LOW);
            shiftOut(pinArray[2], pinArray[0], MSBFIRST, commonAnode ? ~dataArray[number] : dataArray[number]);  
            digitalWrite(pinArray[1], HIGH);
        }
        else
            this->print(number);
    }
}

void SevSeg::print(int number, bool zeros) {
    // Only shift register is allowed
	if (!shiftRegister) {
        return;
    }
            
    digitalWrite(pinArray[1], LOW);
    for (byte c = 0; c < numberOfDisplays; c++) {
        // Prints the units of number
        shiftOut(pinArray[2], pinArray[0], MSBFIRST, commonAnode ? ~dataArray[number%10] : dataArray[number%10]);  
        
        // Shifts right (in base 10)
        number /= 10;
        
        // Note: first zero is printed
        if (number == 0) {
            for (byte k = c; k < numberOfDisplays; k++) {
                shiftOut(pinArray[2], pinArray[0], MSBFIRST, commonAnode ? 0xF : 0x0);  
            }
            
            break;
        }
    }
    digitalWrite(pinArray[1], HIGH);
}

// Deallocates the dynamic data
SevSeg::~SevSeg() {
    delete[] pinArray;
}
