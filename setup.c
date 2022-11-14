/********************************************************************************
* setup.c: Innehåller initieringsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
*
*        1. Vi sätter lysdioden till utport genom att ettställa motsvarande
*           bit i datariktningsregister DDRB (Data Direction Register B).
*
*        2. Vi initierar AD-omvandlaren genom att köra en testomvandling.
*           De analoga kretsarna initieras då vid start. Returtypen typomvandlas
*           till void då vi inte är intresserade av returvärdet vid start.
********************************************************************************/
void setup(void)
{
   set(DDRB, LED1);
   (void)adc_read(POT1);
   return;
}