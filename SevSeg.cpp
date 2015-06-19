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

SevSeg::SevSeg( byte clock, byte latch, byte data, boolean _commonAnode) {
    commonAnode = _commonAnode;
    shiftRegister = true;
    
    pinArray = new byte[3];
    pinArray[0] = clock;
    pinArray[1] = latch;
    pinArray[2] = data;
    
    for (byte set=0; set<3; set++){
        pinMode(pinArray[set],OUTPUT);
    }

}

// Prints the number on the display
void SevSeg::print(byte number) {
	if (!shiftRegister) {
        for (byte c = 0, dataTmp = dataArray[number]; c < 7; c++, dataTmp = dataTmp >> 1) {
            digitalWrite(pinArray[c], commonAnode ? !(dataTmp & 0x01) : dataTmp & 0x01);
        }
        
    }
    else {
        digitalWrite(pinArray[1], LOW);
        shiftOut(pinArray[2], pinArray[0], MSBFIRST, commonAnode ? ~dataArray[number] : dataArray[number]);  
        digitalWrite(pinArray[1], HIGH);
    }
}

// Deallocates the dynamic data
SevSeg::~SevSeg() {
    delete[] pinArray;
}
