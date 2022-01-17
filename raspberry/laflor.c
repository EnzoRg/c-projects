#include "funciones.h"

int laflor(int velocidad)
{
	pioInit();
	mapeo_puertos();

	int i,j, key = 0;
	int sec[14][8]=
	{
		{0,0,0,1,1,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,1,1,1,1,0,0},
		{0,0,1,1,1,1,0,0},
		{0,1,0,1,1,0,1,0},
		{0,1,0,1,1,0,1,0},
		{1,0,1,0,0,1,0,1},
		{1,0,1,0,0,1,0,1},
		{1,1,0,0,0,0,1,1},
		{1,1,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		
	};
	int salida[]={23,24,25,12,16,20,21,26};

	printf("La flor que florece\n");
	printf("Presione Esc para finalizar la secuencia\n");
	 
	while(key != ESC)
	{
		for(i=0;i<14;i++)
		{	
			for(j=0;j<8;j++)
			{
				digitalWrite(salida[j], sec[i][j]);
				
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
			}
			
			velocidad = demora(velocidad);
		}
	}

	return 0;
}
