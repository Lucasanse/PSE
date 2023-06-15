#include "timer.h"
#include "serial.h"
#include "adc.h"
#include <avr/interrupt.h>

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;

void sleep_ms(unsigned int tiempo)
{
    volatile long i;
    for(i = 0; i < tiempo * 180; i++){
    }
}

//el servo se para en 720
/*El servo se mueve en sentido horario con velocidades de 520 a 720*/
/*El servo se mueve en sentido antihorario en velocidades de 720 a 920*/
/*El servo se conecta en el pin D9*/
void main()
{
  *(DDR_B)=0b00100110;
  timer1_init();
  serial_init(); 
  adc_init();

  unsigned int velocidad_inicial = 920;
  unsigned int val;
  volatile long i;
  
  while(1){
     /* determinamos la velocidad y direccion*/
    //val =  velocidad_inicial - ((adc_get(2)/150)*20); /* obtener una conversión ADC del pin de entrada ADC 2 */
    val = 0;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 30;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 60;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 90;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 120;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 150;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    val = 180;
    velocidad(val);
    for(i = 0; i < 180000; i++){}
    //sleep_ms(1000);
  }
  for(;;);
}

void velocidad(int vel){
    serial_put_string("\n\r servo a velocidad: ");
    serial_put_int(vel,4);
    timer1_fijar_angulo(vel);
    sleep_ms(1000);
}

