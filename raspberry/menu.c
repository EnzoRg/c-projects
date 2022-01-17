#include "funciones.h"

void menu()
{
	int op, velocidad;
		
	velocidad = adc_pi(); 
	
	do{

		system("clear");	
	
		printf("Tecnicas Digitales II\n");	
		printf("Tiempo por ciclo: %d mS\n", velocidad);
		printf("Ingrese la opcion deseada:\n");
		printf("	1) -Auto fantastico\n");
		printf("	2) -La carrera\n");
		printf("	3) -El choque\n");
		printf("	4) -La apilada\n");
		printf("	5) -El rebote\n");
		printf("	6) -Güiro\n");
		printf("	7) -Parpadeo pares e impares\n");
		printf("	8) -Flor\n");
		printf("	9) -Trabajo remoto\n");
		printf("	10)-Velocidad\n");
		printf("	11)-Salir\n");
		printf("Opcion: ");
		scanf("%d", &op);

		switch(op)
		{
			case 1:
				system("clear");
				velocidad = auto_fantastico(velocidad);
				break;

			case 2:
				system("clear");
				velocidad = la_carrera(velocidad);
				break;
	
			case 3:
				system("clear");
				velocidad = choque(velocidad);
				break;
		
			case 4:
				system("clear");
				velocidad = apilada(velocidad); 
				break;

			case 5:
				system("clear");
				velocidad = rebote(velocidad);
				break;

			case 6:
				system("clear");
				velocidad = guiro(velocidad);
				break;
				
			case 7:
				system("clear");
				velocidad = impares(velocidad);
				break;	
				
			case 8:
				system("clear");
				velocidad = laflor(velocidad);
				break;	
				
			case 9:
				system("clear");
				maestro();
				break;
				
			case 10:
				system("clear");
				velocidad = velocidad_pot();
				break;
				
			case 99:
				system("clear");
				integrantes();
				break;
				
			default:
				system("clear");
				break;

		}
	}while(op!=11);

	printf("Saliendo del programa...\n");
}
