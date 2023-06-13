
#include <avr/interrupt.h>
volatile int ticks = 0;

typedef struct
{
    uint8_t tccr1a;  /* Registro de control A del timer1 */
    uint8_t tccr1b;  /* Registro de control B del timer1 */
    uint8_t tccr1c;  /* Registro de control C del timer1 */
    uint8_t reserved;
    uint8_t tcnt1l;  /* Registro timer/contador parte baja*/
    uint8_t tcnt1h;  /* Registro timer/contador parte alta*/
    uint8_t icr1l;   /* Registro de captura de entrada Byte parte baja*/
    uint8_t icr1h;   /* Registro de captura de entrada Byte parte alta*/
    uint8_t ocr1al;  /* Registro comparador A parte baja*/
    uint8_t ocr1ah;  /* Registro comparador A parte alta*/
    uint8_t ocr1bl;  /* Registro comparador B parte baja*/
    uint8_t ocr1bh;  /* Registro comparador B parte alta*/

} volatile timer1_t;


volatile timer1_t *timer1 = (timer1_t *)(0x80);

/* registro mascara de interrupciones timer 1 */
volatile unsigned char *timer1_timsk1 = (unsigned char *)(0x6F);

#define SYSTEM_TICKS 4000000
#define PRESCALAR 8

/*con el preescalar 8 hace 10000 ticks en 20 ms, 500 en 1ms y 1000 en 2ms*/

#define TIMER1_CS 0x02  /* prescalar = 8*/
#define TIMER1_CTC 0x80 /* OC1A no invertido*/

#define TIMER1_WG0 0x02 /* Fast PWM TOP ICR1*/
#define TIMER1_WG1 0x18 /* Fast PWM TOP ICR1*/

#define TIMER1_ICR1H 0x27  /* ICR1 = 10000*/
#define TIMER1_ICR1L 0x10


void timer1_init( void )
{
	timer1->tccr1a = (TIMER1_CTC | TIMER1_WG0) ;
	timer1->tccr1b = (TIMER1_CS | TIMER1_WG1) ;

	timer1->icr1h = TIMER1_ICR1H; /* define la parte alta de TOP del contador */
	timer1->icr1l = TIMER1_ICR1L; /* define la parte baja de TOP del contador */

	(*timer1_timsk1) |= 0x01;  /* 0x01: al producirse overflow se dispara una interrupcion*/ 

  /* el ocr1 corresponde al pin D9 del arduino*/
	timer1-> ocr1ah = 0;
  timer1-> ocr1al = 0;
	
}

/* rutina de atencion de interrupciones*/

ISR(TIMER0_COMPA_vect)
{
  ticks++;
  if(ticks==1000){
    /* paso un segundo */  
  }
  
  
}

void timer1_rotacion_servo(int num){
  timer1-> ocr1ah = num >> 8;
  timer1-> ocr1al = num;
}