#include <SevSeg.h>

SevSeg display = SevSeg(9, 10, 11, COMMON_ANODE);

const byte PINbottoni[3] = {2, 3, 4};
byte punteggio = 0;

void setup() {
  for (c = 0; c < 3; c++) {
    pinMode(PINbottoni[c], INPUT);
  }

  display.print(0);  // Inizializza il display a 0
}

void loop()
{
  switch ( QualeHoPremuto() ) {
    case 0:  // Incrementa
      if (punteggio < 9)
        punteggio++;

      display.print(punteggio);

      break;
    case 1:  // Decrementa
      if (punteggio > 0)
        punteggio--;
        
      display.print(punteggio);

      break;

    case 2:
            punteggio = 0;
        
      display.print(punteggio);
    
      break;
  }

  delay(50);
}

