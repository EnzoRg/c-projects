#include "funciones.h"

char uart_envia (int serial_port)		//Envía un carácter por puerto serie
{
  char dato;

  printf ("Ingrese instruccion: ");
  
  getchar();					//Se utiliza para descartar el "ENTER" que se presiona al ingresar un caracter
  dato=getchar();

  serialPutchar(serial_port, dato);		//Envia un unico byte por el puerto serie indicado
	
  return dato;	
  				//Devuelve lo enviado
}

