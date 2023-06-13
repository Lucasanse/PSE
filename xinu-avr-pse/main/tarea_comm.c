/*
 * tarea_comm: esta tarea utiliza la comunicacion serial UART
 *             para enviar un mensaje.
 * 
 * Se desarrolla como un programa aislado del resto.
 */

#include <xinu.h>
#include "serial.h"
#include "globales.h"


#define SEM_COM 0
#define SEM_PROD 1

int comunicacion(void)
{
	while(1) {
		/* como esta tarea comparte el serial con otra tarea, 
		 * se lo sincroniza estilo productor-consumidor,
		 * para que cada uno envie un mensaje de manera
		 * alternada.
		 */
		sync_wait(SEM_PROD);
			serial_put_str("ESTA CAMBIADO: ");
			serial_put_int(angulo_servo,4);
			serial_put_str("\n");
		sync_signal(SEM_COM);
		
		sleep(2);
	}

}

