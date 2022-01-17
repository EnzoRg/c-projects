#include "funciones.h"

int integrantes()
{
	int key = 0;
	
	printf("Hola\n");  //Cambiar por nombres y legajos 
	
	while(key != ESC)
	{
		if(kbhit())
			key = getchar();
	}
	
	return 0;
	
}
