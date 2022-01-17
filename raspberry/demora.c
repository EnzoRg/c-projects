#include "funciones.h"

int demora(int velocidad)
{
	if (velocidad < MIN)
		velocidad = MIN;
	else if (velocidad > MAX)
		velocidad = MAX;
		
	delayMillis(velocidad);
	return velocidad;
}
