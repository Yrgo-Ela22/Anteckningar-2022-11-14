/********************************************************************************
* header.h: Innehåller diverse definitioner och deklarationer för implementering
*           av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (behövs för fördröjningsrutiner): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>     /* Innehåller information om I/O-register såsom PORTB. */
#include <util/delay.h> /* Innehåller fördröjningsrutiner såsom _delay_ms. */
 
/* Makrodefinitioner: */
#define LED1 PORTB0 /* Lysdiod 1 på pin 8 (PORTB0). */
#define POT1 PORTC0 /* Potentiometer 1 på analog pin A0 (PORTC0). */

/********************************************************************************
* set: Ettställer angiven bit i angivet register utan att påverka övriga bitar.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten i registret som ska ettställas.
********************************************************************************/
#define set(reg, bit) reg |= (1 << bit)

/********************************************************************************
* clr: Nollställer angiven bit i angivet register utan att påverka övriga bitar.
*
*      - reg: Registret som skrivning ska ske till.
*      - bit: Biten i registret som ska nollställas.
********************************************************************************/
#define clr(reg, bit) reg &= ~(1 << bit)

/********************************************************************************
* delay_ms: Genererar fördröjning mätt i millisekunder.
*
*           - delay_time_ms: Pekare till angiven fördröjningstid.
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
* adc_read: Läser av den analoga insignalen från angiven pin och returnerar
*           motsvarande digitala värde mellan 0 - 1023.
*
*           - pin: Analog pin A0 - A5 vars insignal ska läsas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin);

/********************************************************************************
* adc_get_pwm_values: Läser av insignalen från angiven pin och beräknar sedan
*                     on- och off-tid utefter angiven periodtid för PWM.
*
*                     - pin: Analog pin A0 - A5 vars insignal ska läsas av.
*                     - pwm_period_ms: Periodtiden för PWM i millisekunder.
*                     - pwm_on_ms    : Adress där on-tiden för PWM lagras..
                      - pwm_off_ms   : Adress där off-tiden för PWM lagras.
********************************************************************************/
void adc_get_pwm_values(const uint8_t pin,
                        const uint8_t pwm_period_ms,
                        uint8_t* pwm_on_ms,
                        uint8_t* pwm_off_ms);

#endif /* HEADER_H_ */