/********************************************************************************
* adc.c: Innehåller funktionalitet för AD-omvandling.
********************************************************************************/
#include "header.h"

/********************************************************************************
* adc_read: Läser av den analoga insignalen från angiven pin och returnerar
*           motsvarande digitala värde mellan 0 - 1023.
*
*           1. Vi väljer intern matningsspänning samt analog kanal via skrivning
*              till register ADMUX. REFS0 ettställs för matningsspänningen,
*              medan pin-numret avgör vilken analog kanal som kopplas till
*              AD-omvandlaren.
*
*           2. Vi aktiverar AD-omvandlaren, startar AD-omvandling direkt och
*              använder lägsta möjliga frekvens 125 kHz så att AD-omvandlaren
*              får extra tid att göra en bra AD-omvandling. Vi sätter prescaler-
*              bitar ADPS[2:0] till divisionsfaktor 128, så vi får en frekvens
*              på 16 MHz / 128 = 125 kHz för AD-omvandlingen.
*
*           3. Vi väntar sedan på att AD-omvandlingen slutförs, vilket indikeras
*              via biten ADIF (ADC Interrupt Flag), som då ettställs. Så länge
*              ADIF är lika med noll så gör vi ingenting. En tom while-sats körs
*              därmed så länge ADIF är lika med 0.
*
*           4. Vi nollställer sedan biten ADIF inför nästa AD-omvandling (så
*              att signalerar som den ska även då) genom att ettställa denna.
*              Notera alltså, vi ettställer ADIF, vilket gör att den sedan
*              nollställs av hårdvaran.
*
*           5. Vi returnerar det 10-bitars resultatet som ligger i register ADC.
*
*           - pin: Analog pin A0 - A5 vars insignal ska läsas av.
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
* adc_get_pwm_values: Läser av insignalen från angiven pin och beräknar sedan
*                     on- och off-tid utefter angiven periodtid för PWM.
*
*                     1. Vi läser av angiven pin och beräknar duty cycle som ett
*                        flyttal mellan 0 - 1. Duty cycle indikerar hur stort
*                        andel av perioden som lysdioden ska vara tänd,
*                        exempelvis 0.6 indikerar att lysdioden ska vara på
*                        60 % av tiden, vilket ger 60 % ljusstyrka. För att
*                        beräkna duty cycle beräknar vi ration mellan omvandlad
*                        insignal dividerat med maximal insignal 1023.0.
* 
*                     2. Vi beräknar on-tiden, alltså tiden som lysdioden
*                        ska vara tänd, genom att multiplicera vår duty cycle
*                        mer periodtiden. Exempelvis, om duty cycle är 0.6 och
*                        vi har en periodtid på 10 ms, så får vi en on-tid på
*                        0.6 * 10m = 6 ms. Lysdioden ska då vara tänd i 6 ms
*                        och släckt resten av perioden, alltså 10m - 6m = 4 ms.   
*                        Vi avrundar detta till närmsta heltal genom att addera.
*
*                     3. Vi beräknar off-tiden som periodtiden - on-tiden, 
*                        alltså som resterande periodtid.
*
*                     - pin: Analog pin A0 - A5 vars insignal ska läsas av.
*                     - pwm_period_ms: Periodtiden för PWM i millisekunder.
*                     - pwm_on_ms    : Adress där on-tiden för PWM lagras..
                      - pwm_off_ms   : Adress där off-tiden för PWM lagras.
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