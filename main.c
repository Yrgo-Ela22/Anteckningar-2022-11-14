/********************************************************************************
* main.c: Demonstration av ett inbyggt system inneh�llande en potentiometer f�r
*         styrning av ljusstyrkan p� en lysdiod via PWM-generering. 
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Ansluter en lysdiod till pin 8 (PORTB0) samt en potentiometer till
*       analog pin A0 (PORTC0). Mikrodatorn initieras genom att lysdiodens pin 
*       s�tts till utport och AD-omvandlarens analoga kretsar initieras via en 
*       testomvandling. 
*
*       D�refter sker kontinuerligt avl�sning av den analoga insignalen fr�n
*       fr�n potentiometern, som varierar mellan 0 - 5 V. Denna signal omvandlas 
*       till en digital motsvarighet mellan 0 - 1023, som sedan anv�nds f�r att 
*       ber�kna duty cycle, som indikerar hur stor andel av aktuell periodtid som 
*       lysdioden ska vara t�nd. 
*
*       Som exempel, om potentiometern vrids klockvis till 60 % av max (den 
*       analoga insignalen b�r d� bli 5 * 0.6 = 3 V) s� erh�lls en duty cycle 
*       p� 0.6, vilket inneb�r att lysdioden ska vara t�nd 60 % av periodtiden, 
*       i detta fall 6 ms f�r en periodtid p� 10 ms. Resterande 4 ms av 
*       periodtiden ska lysdioden vara sl�ckt. Den tid som lysdioden ska h�llas 
*       t�nd respektive sl�ckt varje period kallas on-tid respektive off-tid. 
*
*       Ur duty cycle samt vald periodtid, i detta fall 10 ms, ber�knas aktuell
*       on- respektive off-tid f�r PWM-genereringen, dvs. hur l�ng tid i 
*       millisekunder som lysdioden ska vara t�nd respektive sl�ckt och lagras
*       i variabler pwm_on_ms samt pwm_off_ms. Utefter erh�llna v�rden styrs 
*       lysdiodens ljusstyrka via en blinkning med ber�knad on- och off-tid.
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

