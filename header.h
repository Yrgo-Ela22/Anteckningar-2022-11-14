/********************************************************************************
* header.h: Inneh�ller diverse definitioner och deklarationer f�r implementering
*           av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (beh�vs f�r f�rdr�jningsrutiner): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>     /* Inneh�ller information om I/O-register s�som PORTB. */
#include <util/delay.h> /* Inneh�ller f�rdr�jningsrutiner s�som _delay_ms. */
 
/* Makrodefinitioner: */
#define LED1 PORTB0 /* Lysdiod 1 p� pin 8 (PORTB0). */
#define POT1 PORTC0 /* Potentiometer 1 p� analog pin A0 (PORTC0). */

/********************************************************************************
* set: Ettst�ller angiven bit i angivet register utan att p�verka �vriga bitar.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten i registret som ska ettst�llas.
********************************************************************************/
#define set(reg, bit) reg |= (1 << bit)

/********************************************************************************
* clr: Nollst�ller angiven bit i angivet register utan att p�verka �vriga bitar.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten i registret som ska nollst�llas.
********************************************************************************/
#define clr(reg, bit) reg &= ~(1 << bit)

/********************************************************************************
* delay_ms: Genererar f�rdr�jning m�tt i millisekunder.
*
*           - delay_time_ms: Pekare till angiven f�rdr�jningstid.
********************************************************************************/
#define delay_ms(delay_time_ms) ({ \
   for (uint16_t i = 0; i < *delay_time_ms; ++i) { \
      _delay_ms(1); \
   } \
})

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
********************************************************************************/
void setup(void);

/********************************************************************************
* adc_read: L�ser av den analoga insignalen fr�n angiven pin och returnerar
*           motsvarande digitala v�rde mellan 0 - 1023.
*
*           - pin: Analog pin A0 - A5 vars insignal ska l�sas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin);

/********************************************************************************
* adc_get_pwm_values: L�ser av insignalen fr�n angiven pin och ber�knar sedan
*                     on- och off-tid utefter angiven periodtid f�r PWM.
*
*                     - pin: Analog pin A0 - A5 vars insignal ska l�sas av.
*                     - pwm_period_ms: Periodtiden f�r PWM i millisekunder.
*                     - pwm_on_ms    : Adress d�r on-tiden f�r PWM lagras..
                      - pwm_off_ms   : Adress d�r off-tiden f�r PWM lagras.
********************************************************************************/
void adc_get_pwm_values(const uint8_t pin,
                        const uint8_t pwm_period_ms,
                        uint8_t* pwm_on_ms,
                        uint8_t* pwm_off_ms);

#endif /* HEADER_H_ */