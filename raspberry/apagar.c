#include "funciones.h"
#include "EasyPIO.h"

void apagar (void)
{
	int leds[]={23,24,25,12,16,20,21,26};
	int i;

	for(i=0;i<8;i++)
		digitalWrite(leds[i],0);

}
