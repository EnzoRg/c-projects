/* funciones.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "EasyPIO.h"

extern int 	password		(void);
extern int	kbhit			(void);
extern int 	adc_pi			(void);
extern int 	velocidad_pot	(void);
extern int	maestro			(void);
extern int	integrantes		(void);

extern int	auto_fantastico	(int velocidad);
extern int 	la_carrera		(int velocidad);
extern int 	choque			(int velocidad);
extern int 	apilada			(int velocidad);

extern int 	rebote	(int velocidad);
extern int 	guiro	(int velocidad);
extern int 	impares	(int velocidad);
extern int 	laflor	(int velocidad);
extern int 	demora	(int velocidad);

extern void menu			(void);
extern void mapeo_puertos	(void);
extern void apagar			(void);

extern char uart_envia 	(int serial_port);
extern char uart_recibe (int serial_port);
extern char uart_adc 	(int serial_port);

#define ESC 	27
#define T		1.961
#define MIN		30
#define MAX 	500
#define	STEP	30

/* Defines de password */
#define N 			6
#define INTENTOS 	3
#define FD_STDIN  	0
#define ENTER		10
