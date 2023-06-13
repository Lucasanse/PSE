
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
   volatile unsigned char * DDR_D = (unsigned char *) 0x2A;
  volatile unsigned char * PUERTO_D = (unsigned char *) 0X2B;

int delay_ms(long tiempo){
  //aca hay que ver cuantos i necesito ciclar para llegar a 1ms 
  //con 150 iteraciones hacemos 1ms, va a pasar como parametro cuantos ms necesitamos 
  //esto lo verificamos con el osciloscopio 
  long cant=150*tiempo;
  volatile long i;
  for (i = 0; i < cant; i++){}
}


/*
CONTADOR DIGIRAL CONTANDO DE ARRIBA A ABAJO DE IZQUIERDA A DERECHA

P1= el del medio 
P2 = arriba a la izquierda
P3 = gnd
P4 = arriba al medio  
P5 = arriba a la derecha  
P6 = abajo a la izquierda
P7 = abajo al medio 
P8 = gnd
P9 = abajo a la derecha
P10 = el punto.   
*/

/*
En esta implementacion 
P1 = D12 PB4 el del medio 
P2 = D11 PB3 arriba a la izquierda
P4 = D10 PB2 arriba al medio 
P5 = D9  PB1 arriba a la derecha
P6 = D8  PB0 abajo a la izquierda
P7 = D7  PD7 abajo al medio 
P9 = D6  PD6 abajo a la derecha

*/

void numero (int num){
  switch (num)
  {
  case 1: //P5 P9
    *(PUERTO_B) = 0b11111101;
    *(PUERTO_D) = 0b10111111;
    break;
  case 2: //P1 P4 P5 P6 P7
    *(PUERTO_B) = 0b11101000;
    *(PUERTO_D) = 0b01111111;
    break;
  
  default:
    break;
  }
}
int main(void)
{

  *(DDR_B)=0b00111111;
  *(DDR_D)=0b11111100;
  while(1){
    numero(1);
    delay_ms(1000);
    numero(2);
    delay_ms(1000);
}
}