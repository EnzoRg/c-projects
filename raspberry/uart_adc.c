#include "funciones.h"

char uart_adc (int serial_port)
{
	int val_adc;
	
	val_adc=adc_pi();
	
	serialPutchar(serial_port, val_adc);
	
	return  val_adc;

}
