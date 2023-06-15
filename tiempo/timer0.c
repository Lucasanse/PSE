
/* timer0/counter de 8bits: ejemplo que genera 1000 interrupciones por segundo.
 *
 * 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 * Utilizamos modo CTC, el cual compara con TOP. TOP es definido por OCR0A. 
 * Cuando CONTADOR == TOP el CONTADOR se pone a cero.
 *
 * reloj del sistema: 4000000 de ticks/s  /  8 (prescalar) = 500000 ticks/s
 *
 * 500000 ticks/s  /  250 = 2000 ticks/s => 
 */

#include <avr/io.h>
#include <avr/interrupt.h>


#define TIMER0_CS 0x02 /* prescalar=8 CS02|CS01|CS00 = 0b010 */
#define TIMER0_CTC 0x02 /* CTC = WGM = 0b010 : modo CTC es comparar y volver a cero*/

#define SYSTEM_TICKS 4000000
#define PRESCALAR 8
#define TICKS_PER_SECOND 2000

#define TIMER0_OCR0A (SYSTEM_TICKS/PRESCALAR/TICKS_PER_SECOND)


typedef struct
{
    uint8_t tccr0a; /* Registro de control A del timer0 */
    uint8_t tccr0b; /* Registro de control B del timer0 */
    uint8_t tcnt0;  /* Registro timer/contador */
    uint8_t ocr0a;  /* Registro comparador A */
    uint8_t ocr0b;  /* Registro comparador B */

} volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);



/* registro mascara de interrupciones timer 0 */
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

volatile int ticks;
unsigned char hora = 0;
unsigned char min = 0;
unsigned char seg = 0;

void timer0_init( void )
{
	timer0->tccr0a |= TIMER0_CTC;
	timer0->tccr0b |= TIMER0_CS;
	timer0->ocr0a = TIMER0_OCR0A; /* valor contra el cual comparar */
	(*timer0_timsk0) |= 0x02;  /* 0x02: compara contra registro OCR0A 
				      y genera interrupcion si hay un match */
	ticks = 0;
}

ISR(TIMER0_COMPA_vect)
{
    ticks ++;
	/* pasó un segundo */
    if (ticks == 2000) {
		seg++;
		if(seg == 60){
			min ++;
			seg = 0;
			if(min == 60){
				hora++;
				min=0;
				if(hora = 24){
					hora=0;
				}
			}
		} 
	ticks = 0;

   }
}

int get_ticks()
{
	return ticks;
}

unsigned char get_seg(){
	return seg;
}

unsigned char get_min(){
	return min;
}

unsigned char get_hora(){
	return hora;
}
