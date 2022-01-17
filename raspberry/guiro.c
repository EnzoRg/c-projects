#include "funciones.h"

int guiro(int velocidad)
{
	pioInit();
	mapeo_puertos();
		
	int leds[]={23,24,25,12,16,20,21,26};
	
	int i,k,j,key=0;
	printf("Siga el ritmo del Güiro\n");
	printf("Presione Esc para finalizar la secuencia\n");
	
	while(key != ESC)
	{
		for (k=0; k<2;k++)
		{
			for (j=0; j<3;j++)
			{ 
				if (j<2)
				{
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
								velocidad -= 30;
							if( key == 's')
								velocidad += 30;
						}
						digitalWrite(leds[i],0);
					}
				}
			else
			{
				for(i=0; i<8; i++)
				{
					digitalWrite(leds[i],1);
					demora(velocidad);
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
							velocidad -= 30;
						if( key == 's')
							velocidad += 30;
					}
					digitalWrite(leds[i],0);
				}		
			}
							}
							}
		for(k=0;k<2;k++){
			for(i=7; i>=0; i--)
	   {	
			 digitalWrite(leds[i],1);
			demora(velocidad);
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
						velocidad -= 30;
					if( key == 's')
						velocidad += 30;
				 }
			 digitalWrite(leds[i],0);
		}
			for(i=0; i<8; i++)
		{
			digitalWrite(leds[i],1);
			demora(velocidad);
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
						velocidad -= 30;
					if( key == 's')
						velocidad += 30;
			}
			digitalWrite(leds[i],0);
		}				}
	}
	
	return 0;
}
