

  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  volatile unsigned char * PIN_B= (unsigned char *) 0X23;
  
int main(void)
{

  (*DDR_B)= 0b00001000;//d12= ENTRADA, d11=SALIDA

	serial_init();
  
  int distancia_cm =0;
  unsigned int tiempo_us;
  volatile int echo = 0;
  volatile unsigned int t=0;

  while(1){//
    (*PUERTO_B)= (*PUERTO_B) | 0b00001000;//Activa salida
    sleep10_us();//Espera 10us
    (*PUERTO_B)= (*PUERTO_B) & 0b11110111;//Desactiva salida
    t=0;
    while(!echo){
      echo = (*PIN_B) & 0b00010000;
    }//Se queda esperando que se habilite la entrada
 
    while(echo){
      t++;
      sleep10_us();//Espera 10us*/
      echo = (*PIN_B) & 0b00010000;//Actualiza entrada
    }
    tiempo_us = t * 10;  
    distancia_cm = tiempo_us / 58;
    serial_put_str("\n\rdistancia: ");
    serial_put_int(distancia_cm,4);//Mostrar distancia
    serial_put_str(" cm");
    sleep_ms(50);

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

