/********************************************************************************
* setup.c: Inneh�ller initieringsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
*
*        1. Vi s�tter lysdioden till utport genom att ettst�lla motsvarande
*           bit i datariktningsregister DDRB (Data Direction Register B).
*
*        2. Vi initierar AD-omvandlaren genom att k�ra en testomvandling.
*           De analoga kretsarna initieras d� vid start. Returtypen typomvandlas
*           till void d� vi inte �r intresserade av returv�rdet vid start.
********************************************************************************/
void setup(void)
{
   set(DDRB, LED1);
   (void)adc_read(POT1);
   return;
}