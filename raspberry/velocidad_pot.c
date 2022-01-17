#include "funciones.h"

int velocidad_pot()
{
	int velocidad, key=0;
	
	while(key != ESC)
	{
		system("clear");
		velocidad = adc_pi(); 

		printf("Presione Esc para finalizar la secuencia\n");
		printf("Varíe el potenciometro para variar la velocidad\n\tTenga en cuenta que el tiempo minimo es %dmS y el maximo %dmS\n\tTiempo por ciclo = %d mS\n",MIN, MAX, velocidad);
		delay(80);
		
		if(kbhit())
		{
			key = getchar();
			if( key == ESC)
			{	
				printf("\nSecuencia finalizada\n");
				return velocidad;				
			}
		}
	}
	
	return 0;
	
}
