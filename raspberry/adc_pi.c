#include "funciones.h"

const char PCF8591 = 0x48; // direccion base

int fd, adcVal;	//declaracion de variables para acceder al adc

int adc_pi()   
{

	if (wiringPiSetup () == -1) 
		exit (1);	

	fd = wiringPiI2CSetup(PCF8591);		
	wiringPiI2CReadReg8(fd, PCF8591 + 0) ; 
	adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 0) ;
			  
	adcVal *= T; //Como el A/D es de 8bits se debee multiplicar por una constante para obtener un rango de 500mS

	if(adcVal < MIN) 
		adcVal = MIN;
	else if (adcVal > MAX)
		adcVal = MAX;
	
	delay(20);
	
	printf("%d\n", adcVal);
	
	return adcVal;		  
}


