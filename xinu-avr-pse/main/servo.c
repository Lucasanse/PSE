#include <xinu.h>
#include "globales.h"
#include "timer.h"
volatile int last_angle=0;

int mover_servo(void)
{
  while(1){
    if(angulo_servo == 1){
      timer1_rotacion_servo(920);
    }
    else{
      timer1_rotacion_servo(520);
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}