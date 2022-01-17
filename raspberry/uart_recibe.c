#include "funciones.h"

char uart_recibe (int serial_port)	//Lee un carácter del puerto serie
{

  char dat;

  dat=0;

  while(dat==0) //Se ejecuta hasta que se lea un caracter
  {			
    if(serialDataAvail (serial_port)) 		// Retorna el numero de caracteres disponibles para leer o -1*/
    {
      dat = serialGetchar (serial_port);			// Retorna el siguiente carácter
 		//disponible en el dispositivo serial 	
    }
  }

  serialFlush(serial_port);	 			//Borra todo lo que haya en el puerto
  
  return dat;	
  					//Devuelve lo recibido
}

