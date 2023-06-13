#include "adc.h"
#include "serial.h"


main()
{
 int val;
 adc_init();
 serial_init();
 serial_put_string("Inicia el programa");

 while(1){
    
   
    val = (adc_get(2)/380); /* obtener una conversión ADC del pin de entrada ADC 2 */

    serial_put_int(val,4); 
    serial_put_string("\n \r");
    sleep_ms(200);
 }

}

void sleep10_us()
{
  for (volatile int i = 0; i < 1; i++){
  }
  volatile int a=1;
  
}

void sleep_ms(int tiempo)
{
  volatile unsigned int cant=146*tiempo;
  for (volatile long i = 0; i < cant; i++){}
}