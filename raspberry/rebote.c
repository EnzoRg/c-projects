#include "funciones.h"

int rebote(int velocidad)
{
	pioInit();
	mapeo_puertos();
		
	int leds[]={23,24,25,12,16,20,21,26};
	
	int i,key=0;
	printf("Rebote \n");
	printf("Presione Esc para finalizar la secuencia\n");
	
	while(key != 27)
	{
		digitalWrite(leds[0],1);
		for(i=7; i>=1; i--)
		{	
			digitalWrite(leds[i],1);
			velocidad = demora(velocidad);
			if(kbhit())
			{
				key = getchar();
				if( key == 27)
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
		for(i=2; i<7; i++)
		{
			digitalWrite(leds[i],1);
			demora(velocidad*2);
			if(kbhit())
			{
					key = getchar();
					if( key == 27)
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
	  				
	}
	
	return 0;
  
}
