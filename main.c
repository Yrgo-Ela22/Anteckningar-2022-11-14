/********************************************************************************
* main.c: Demonstration av ett inbyggt system innehållande en potentiometer för
*         styrning av ljusstyrkan på en lysdiod via PWM-generering. 
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Ansluter en lysdiod till pin 8 (PORTB0) samt en potentiometer till
*       analog pin A0 (PORTC0). Mikrodatorn initieras genom att lysdiodens pin 
*       sätts till utport och AD-omvandlarens analoga kretsar initieras via en 
*       testomvandling. 
*
*       Därefter sker kontinuerligt avläsning av den analoga insignalen från
*       från potentiometern, som varierar mellan 0 - 5 V. Denna signal omvandlas 
*       till en digital motsvarighet mellan 0 - 1023, som sedan används för att 
*       beräkna duty cycle, som indikerar hur stor andel av aktuell periodtid som 
*       lysdioden ska vara tänd. 
*
*       Som exempel, om potentiometern vrids klockvis till 60 % av max (den 
*       analoga insignalen bör då bli 5 * 0.6 = 3 V) så erhålls en duty cycle 
*       på 0.6, vilket innebär att lysdioden ska vara tänd 60 % av periodtiden, 
*       i detta fall 6 ms för en periodtid på 10 ms. Resterande 4 ms av 
*       periodtiden ska lysdioden vara släckt. Den tid som lysdioden ska hållas 
*       tänd respektive släckt varje period kallas on-tid respektive off-tid. 
*
*       Ur duty cycle samt vald periodtid, i detta fall 10 ms, beräknas aktuell
*       on- respektive off-tid för PWM-genereringen, dvs. hur lång tid i 
*       millisekunder som lysdioden ska vara tänd respektive släckt och lagras
*       i variabler pwm_on_ms samt pwm_off_ms. Utefter erhållna värden styrs 
*       lysdiodens ljusstyrka via en blinkning med beräknad on- och off-tid.
********************************************************************************/
int main(void)
{
   uint8_t pwm_on_ms;  
   uint8_t pwm_off_ms; 

   setup(); 

   while (1)
   {
      adc_get_pwm_values(POT1, 10, &pwm_on_ms, &pwm_off_ms);

      set(PORTB, LED1);      
      delay_ms(&pwm_on_ms); 
      clr(PORTB, LED1);      
      delay_ms(&pwm_off_ms); 
   }

   return 0;
}

