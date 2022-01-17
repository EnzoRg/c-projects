#include "funciones.h"

void mapeo_puertos(void)
{
	pioInit();
	
	int swit[]={17,27,5,6,13,19};
	int leds[]={23,24,25,12,16,20,21,26};
	int i;

	for (i=0;i<6;i++)
		pinMode(swit[i], INPUT);

	for(i=0;i<8;i++)
	  pinMode(leds[i], OUTPUT);

}
