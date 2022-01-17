#######################################################################################################
#
#               Makefile Proyecto Tecnicas Digitales II
#
#######################################################################################################

CC = gcc

OBJECTS = main.o password.o menu.o mapeo_puertos.o auto_fantastico.o la_carrera.o apilada.o choque.o rebote.o laflor.o guiro.o impares.o apagar.o demora.o kbhit.o EasyPIO.o adc_pi.o velocidad_pot.o maestro.o uart_envia.o uart_recibe.o uart_adc.o integrantes.o

CFLAGS		= -Wall -O1 -g -c 
WPIFLAGS 	= -lwiringPi

ejecutable: $(OBJECTS)
	$(CC) $(WPIFLAGS) $(OBJECTS) -o ejecutable 

main.o: main.c
	$(CC) $(CFLAGS) main.c 

password.o: password.c
	$(CC) $(CFLAGS) password.c

menu.o: menu.c
	$(CC) $(CFLAGS) menu.c

mapeo_puertos.o: mapeo_puertos.c
	$(CC) $(CFLAGS) mapeo_puertos.c

auto_fantastico.o: auto_fantastico.c
	$(CC) $(CFLAGS) auto_fantastico.c 

apilada.o: apilada.c
	$(CC) $(CFLAGS) apilada.c
	
choque.o: choque.c
	$(CC) $(CFLAGS) choque.c
	
rebote.o: rebote.c
	$(CC) $(CFLAGS) rebote.c
	
impares.o: impares.c
	$(CC) $(CFLAGS) impares.c

laflor.o: laflor.c
	$(CC) $(CFLAGS) laflor.c
	
la_carrera.o: la_carrera.c
	$(CC) $(CFLAGS) la_carrera.c
	
guiro.o: guiro.c
	$(CC) $(CFLAGS) guiro.c	

apagar.o: apagar.c
	$(CC) $(CFLAGS) apagar.c

demora.o: demora.c
	$(CC) $(CFLAGS) demora.c

kbhit.o: kbhit.c
	$(CC) $(CFLAGS) kbhit.c

EasyPIO.o: EasyPIO.c
	$(CC) $(CFLAGS) EasyPIO.c

adc_pi.o: adc_pi.c
	$(CC) $(CFLAGS) adc_pi.c

velocidad_pot.o: velocidad_pot.c
	$(CC) $(CFLAGS) velocidad_pot.c 

maestro.o: maestro.c
	$(CC) $(CFLAGS) maestro.c 

uart_envia.o: uart_envia.c
	$(CC) $(CFLAGS) uart_envia.c 

uart_recibe.o: uart_recibe.c
	$(CC) $(CFLAGS) uart_recibe.c 
	
uart_adc.o: uart_adc.c
	$(CC) $(CFLAGS) uart_adc.c
	
integrantes.o: integrantes.c
	$(CC) $(CFLAGS) integrantes.c 

clean:
	rm *.o  
