#include <xinu.h>
#include "globales.h"
#include "adc.h"
#include "timer.h"

int controlar_motor(void)
{
	while(1) {
		if(motor_encendido) {
			vel_motor = (adc_get(2) / 35);
			if(vel_motor > 100){
				vel_motor=100;
			}
			set_timer1_ocr1b_dutycycle(vel_motor);
		} else {
			set_timer1_ocr1b_dutycycle(0);
		}

		sleepms(50);
	}
}
