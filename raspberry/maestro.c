#include "funciones.h"

int maestro()		//Opción para controlar otra Raspberry Pi
{  
  int serial;

  if ((serial = serialOpen ("/dev/ttyAMA0", 9600)) == -1)			/* abrir el puerto serie /dev/ttyAMA0*/
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 0 ;
  }

//  if (wiringPiSetup () == -1)							/* inicializa la configuracion de wiringPi */
//  {
//    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
//    return 0 ;
//  } 

  char enviado=0;
  
  enviado=uart_adc(serial);
  
  serialFlush(serial);

  while(enviado != '9')		//Si se envía 'x' el programa sale
  {
    system("clear");
    //printf("Presione Esc para finalizar\n");
    printf("Ingrese la opcion deseada:\n");
    printf("	1 -Auto fantastico\n");
    printf("	2 -La carrera\n");
    printf("	3 -El choque\n");
    printf("	4 -La apilada\n");
    printf("	5 -El rebote\n");
    printf("	6 -Guiro\n");
    printf("	7 -Parpadeo pares e impares\n");
    printf("	8 -Flor\n");
    printf("	9 -Salir\n");
    printf("\nUltima instruccion enviada ( z para finalizar la secuencia) : %c \n",enviado);
    
    
    enviado=uart_envia(serial);			//Envía un carácter por puerto serie
  }
  
  system("clear");
  
  return 0;
}

