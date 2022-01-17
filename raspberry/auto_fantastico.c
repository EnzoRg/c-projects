#include "funciones.h"

int auto_fantastico(int velocidad)
{
	pioInit();
	mapeo_puertos();
		
	int leds[]={23,24,25,12,16,20,21,26};
	
	int i,key=0;
	
	printf("Auto Fantastico\n");
	printf("Presione Esc para finalizar la secuencia\n");
	
	while(key != ESC)
	{
		for(i=0; i<8; i++)
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
	   for(i=7; i>=0; i--)
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
	}
	
	return 0;
  
}
