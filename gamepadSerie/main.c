#include "serial.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;


int apretado_izq; //indica si los botones izquierdo o derecho estan apretados
int apretado_der;
int bit_in_izq;
int bit_in_der;
char rcvChar = 0;


int main(void)
{
  *(DDR_B)= 0b00000000;
  *(PUERTO_B)= 0b00001100;//Habilita pullup en pin pb3(d11) y pb2(d10) 
  apretado_izq=0;
  apretado_der=0;

  serial_init();
  serial_put_string("Inicia el programa \r\n");
  while(1){
    
    bit_in_izq = *(PIN_B) & 0b00001000;
    bit_in_der = *(PIN_B) & 0b00000100;
    volatile long i=0;
    if(bit_in_izq==0){//pulldown del boton izquierdo
      delay_rebote();
      serial_put_char('a');
      delay_rebote(); //este delay es para que no haya dos a
      apretado_izq=1;
    }

    if(bit_in_der==0){//pulldown del boton derecho
      delay_rebote();
      serial_put_char('d'); //este delay es para que no haya dos d
      delay_rebote();
      apretado_der=1;
    }
    soltar();
}
}

void soltar ()
{
  if(bit_in_izq!=0 && apretado_izq==1){ 
    //si esta en pullup y se estaba apretando el boton izquierdo manda 'q' 
      delay_rebote();
      serial_put_char('q');
      apretado_izq=0;
  }else if(bit_in_der!=0 && apretado_der==1){
    //si esta en pullup y se estaba apretando el boton derecho manda 'q' 
      delay_rebote();
      serial_put_char('q');
      apretado_der=0;
  }
} 

int delay_rebote(void){
//delay para el rebote de señal
  volatile int i = 0;
  for (i = 0; i < 20000; i++){
  }
}

