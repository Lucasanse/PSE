#include <avr/interrupt.h>
#include <stdio.h>

#include "timer0.h"
#include "serial.h"

int main(void)
{
  int tiempo = 0;
	/* las interrupciones están deshabilitadas */

	/* habilitar las interrupciones */
	timer0_init();
  serial_init();

	cli();
	int ticks_actual = get_ticks();
	int ticks_anterior = ticks_actual-1;
	sei();
        while (1) {
		if((ticks_actual != ticks_anterior) & ticks_actual == 0) {	
      serial_put_int(get_hora(),2);
      serial_put_string(":");
      serial_put_int(get_min(),2);
      serial_put_string(":");
      serial_put_int(get_seg(),2);
      serial_put_string("\n\r");
		}
		cli();
		ticks_anterior = ticks_actual;
		ticks_actual = get_ticks();
		sei();
        }
}



