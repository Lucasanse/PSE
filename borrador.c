/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

/* Estructura de datos del driver ADC */

typedef struct
{
        uint8_t adcl;               /* ADC Data Register Low */
        uint8_t adch;
        uint8_t adcsra;         /* ADC Control and Status Register A */
        uint8_t adcsrb;
        uint8_t admux;                 /* ADC Multiplexer Selection Register */
        uint8_t reserved;
        uint8_t didr0; 

} volatile adc_t;

volatile adc_t *adc = (adc_t *)(0x78); /* direccion del primer registro */


void adc_init()
{
        /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
        de vcc con capacitor externo y encender (habilitar) el periferico */

        adc -> admux = (unsigned char) 0b01000000; //periferico adc0
        
        
        /* Establecer tambien el prescalar para lograr un valor acorde (divisor) */
        adc -> adcsra = (unsigned char) 0b00000100; //16 bits
}

int adc_get(char input)
{
        int val, high, low;

        /* 1. Selects which analog input is connected to the ADC */
        adc -> admux = (adc -> admux & 0b11110000) | input; 

        /* 2. Write this bit to one to start each conversion */

        adc -> adcsra = adc -> adcsra | 0b01000000; 
        
        /* 3. When conversion is complete, it returns to zero */

        while (!((adc-> adcsra) & (0b01000000)));

        /* 4. When conversion is complete, the result is found in these registers */

        /* IMPORTANT: ADCL must be read first, then ADCH */

        low = adc -> adcl;
        high = adc -> adch; 
        val =  high * (2 ^ 8) + low;

        return val;        
}