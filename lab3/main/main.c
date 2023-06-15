#include <xinu.h>
#include "globales.h"
#include "serial.h"
#include "adc.h"
#include "timer.h"

extern int led_testigo(void);
extern int entrada(void);
extern int controlar_motor(void);
extern int controlar_servo(void);

int main(void)
{
	serial_init();
	adc_init();
	timer1_init();

	resume(create(led_testigo, 64, 20, "led", 0));
	resume(create(controlar_servo, 128, 20, "servo", 0));
	resume(create(controlar_motor, 64, 20, "motor", 0));
	resume(create(entrada, 64, 20, "entrada", 0));
	
	while (1){
		segundos ++;
		serial_put_int(segundos / 3600, 2);
		serial_put_char(':');
		serial_put_int((segundos % 3600) / 60, 2);
		serial_put_char(':');
		serial_put_int((segundos % 3600) % 60, 2);
		serial_put_str(".  Velocidad: ");
		serial_put_int(motor_encendido ? vel_motor : 0, 3);
		serial_put_str(". servo: ");
		serial_put_int(angulo_servo, 3);
		serial_put_str(" grados.\n\r");
		sleep(1);
	}


	return 0;
}

