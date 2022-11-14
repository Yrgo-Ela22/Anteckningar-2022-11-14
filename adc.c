/********************************************************************************
* adc.c: Inneh�ller funktionalitet f�r AD-omvandling.
********************************************************************************/
#include "header.h"

/********************************************************************************
* adc_read: L�ser av den analoga insignalen fr�n angiven pin och returnerar
*           motsvarande digitala v�rde mellan 0 - 1023.
*
*           1. Vi v�ljer intern matningssp�nning samt analog kanal via skrivning
*              till register ADMUX. REFS0 ettst�lls f�r matningssp�nningen,
*              medan pin-numret avg�r vilken analog kanal som kopplas till
*              AD-omvandlaren.
*
*           2. Vi aktiverar AD-omvandlaren, startar AD-omvandling direkt och
*              anv�nder l�gsta m�jliga frekvens 125 kHz s� att AD-omvandlaren
*              f�r extra tid att g�ra en bra AD-omvandling. Vi s�tter prescaler-
*              bitar ADPS[2:0] till divisionsfaktor 128, s� vi f�r en frekvens
*              p� 16 MHz / 128 = 125 kHz f�r AD-omvandlingen.
*
*           3. Vi v�ntar sedan p� att AD-omvandlingen slutf�rs, vilket indikeras
*              via biten ADIF (ADC Interrupt Flag), som d� ettst�lls. S� l�nge
*              ADIF �r lika med noll s� g�r vi ingenting. En tom while-sats k�rs
*              d�rmed s� l�nge ADIF �r lika med 0.
*
*           4. Vi nollst�ller sedan biten ADIF inf�r n�sta AD-omvandling (s�
*              att signalerar som den ska �ven d�) genom att ettst�lla denna.
*              Notera allts�, vi ettst�ller ADIF, vilket g�r att den sedan
*              nollst�lls av h�rdvaran.
*
*           5. Vi returnerar det 10-bitars resultatet som ligger i register ADC.
*
*           - pin: Analog pin A0 - A5 vars insignal ska l�sas av.
********************************************************************************/
uint16_t adc_read(const uint8_t pin) 
{
   ADMUX = (1 << REFS0) | pin;  
   ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
   while ((ADCSRA & (1 << ADIF)) == 0);
   ADCSRA = (1 << ADIF); 
   return ADC;
}

/********************************************************************************
* adc_get_pwm_values: L�ser av insignalen fr�n angiven pin och ber�knar sedan
*                     on- och off-tid utefter angiven periodtid f�r PWM.
*
*                     1. Vi l�ser av angiven pin och ber�knar duty cycle som ett
*                        flyttal mellan 0 - 1. Duty cycle indikerar hur stort
*                        andel av perioden som lysdioden ska vara t�nd,
*                        exempelvis 0.6 indikerar att lysdioden ska vara p�
*                        60 % av tiden, vilket ger 60 % ljusstyrka. F�r att
*                        ber�kna duty cycle ber�knar vi ration mellan omvandlad
*                        insignal dividerat med maximal insignal 1023.0.
* 
*                     2. Vi ber�knar on-tiden, allts� tiden som lysdioden
*                        ska vara t�nd, genom att multiplicera v�r duty cycle
*                        mer periodtiden. Exempelvis, om duty cycle �r 0.6 och
*                        vi har en periodtid p� 10 ms, s� f�r vi en on-tid p�
*                        0.6 * 10m = 6 ms. Lysdioden ska d� vara t�nd i 6 ms
*                        och sl�ckt resten av perioden, allts� 10m - 6m = 4 ms.   
*                        Vi avrundar detta till n�rmsta heltal genom att addera.
*
*                     3. Vi ber�knar off-tiden som periodtiden - on-tiden, 
*                        allts� som resterande periodtid.
*
*                     - pin: Analog pin A0 - A5 vars insignal ska l�sas av.
*                     - pwm_period_ms: Periodtiden f�r PWM i millisekunder.
*                     - pwm_on_ms    : Adress d�r on-tiden f�r PWM lagras..
                      - pwm_off_ms   : Adress d�r off-tiden f�r PWM lagras.
********************************************************************************/
void adc_get_pwm_values(const uint8_t pin,
                        const uint8_t pwm_period_ms,
                        uint8_t* pwm_on_ms,
                        uint8_t* pwm_off_ms)
{
   const double duty_cycle = adc_read(pin) / 1023.0;
   *pwm_on_ms = (uint8_t)(duty_cycle * pwm_period_ms + 0.5);
   *pwm_off_ms = pwm_period_ms - *pwm_on_ms;
   return;
}