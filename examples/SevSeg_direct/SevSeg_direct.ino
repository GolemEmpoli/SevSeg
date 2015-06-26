#include <SevSeg.h>

SevSeg display = SevSeg(2,3,4,5,6,7,8, COMMON_ANODE);

void setup(){
   // non c'è niente qui...
}

void loop()
{
  for (byte i=0; i <= 9; i++) {
    display.number(i); // illumina le cifre da 0 a 9
    delay(1000);
  }
}
