#include "funciones.h"

int apilada(int velocidad)
{
	pioInit();
	mapeo_puertos();
		
	int leds[]={23,24,25,12,16,20,21,26};
	
	int i,n,key=0;
	printf("La apilada\n");
	printf("Presione Esc para finalizar la secuencia\n");
	
	while(key != ESC)
	{
		for(n=7; n>=0; n--)
		{
			for(i = 7; i>=7-n; i--)
			{	
				digitalWrite(leds[i],1);
				velocidad = demora(velocidad);
				if(kbhit())
				{
					key = getchar();
					if( key == ESC)
					{	
						apagar();
						printf("\nSecuencia finalizada\n");
						return velocidad;				
					}
					if( key == 'w')
						velocidad -= STEP;
					if( key == 's')
						velocidad += STEP;
				}
				digitalWrite(leds[i],0);
			}
			digitalWrite(leds[7-n],0);
			velocidad = demora(velocidad);
			digitalWrite(leds[7-n],1);
			velocidad = demora(velocidad);
		}		
		
		apagar();
	
	}

	return 0;
}
