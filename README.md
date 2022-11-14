# Anteckningar 2022-11-14
Implementering av AD-omvandling samt PWM för mikrodator ATmega328P.

Filen "header.h" innehåller diverse definitioner samt deklarationer som används för implementering av det inbyggda systemet.

Filen "setup.c" innehåller initieringsrutiner för mikrodatorn.

Filen "adc.c" innehåller rutiner för AD-omvandling av analoga insignaler samt beräkning av on- samt off-tid för PWM-generering.

I filen "main.c" initieras det inbyggda systemet vid start en både sett till konfiguration av I/O-portar samt initiering av AD-omvandlaren. Därefter styrs ljusstyrkan på lysdioden kontinuerligt via avläsning av potentiometern. Utefter styrkan på den analoga insignalen kontrolleras ljusstyrkan via PWM-generering
