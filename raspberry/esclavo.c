int esclavo()			//Opción para recibir instrucciones desde otra Raspberry Pi
{

  char dat;
  if ((serial = serialOpen ("/dev/ttyS0", 9600)) < 0)			/* abrir el puerto serie */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 0 ;
  }

if (wiringPiSetup () == -1)			/* inicializa la configuracion de wiringPi */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 0 ;
  }
	

char opcionesclavo;

while(opcionesclavo!='b')		//Cuando recibe 'b' sale del programa
{system("clear");
  printf (" -------Esperando Instrucción----\n ");

 opcionesclavo=uart_recibe(serial);		//Guarda el carácter recibido


	switch(opcionesclavo)	//Dependiendo lo recibido ejecuta el programa correspondiente
	{
		case '1': system("clear");
			printf("Elegiste la secuencia 'El Auto Fantastico'\n");
			printf("\n Aprete la tecla Esc para salir");
			Autofantastico();
			Apagar();
				break;
		
		case '2': system("clear");
			printf("Elegiste la secuencia 'La Carrera' \n");
			printf("\n Aprete la tecla Esc para salir");
			LaCarrera();
			Apagar();
				break;
		
			
		case '3': system("clear");
			printf("Elegiste la secuencia 'El Choque'\n");
			printf("\n Aprete la tecla Esc para salir");
			ElChoque();
			Apagar();
				break;
		
				
		case '4': system("clear");
			printf("Elegiste la secuencia 'La Apilada'\n");
			LaApilada();
			Apagar();
				break;
		
				
		case '5': system("clear");
			printf("Elegiste Leer Entradas Digitales\n");
			printf("\n Aprete la tecla Esc para salir");
			LeerEntradas();
			Apagar();
				break;
		
		
		case '6': system("clear");
			printf("Elegiste Leer ADC\n");
			LeerADC();
			Apagar();
				break;
		
		

		case '7': system("clear");
			printf("Elegiste Navidad\n");
			printf("\n Aprete la tecla Esc para salir");
			Navidad();
			Apagar();
				break;

		case '8': system("clear");
			printf("Elegiste Ring\n");
			printf("\n Aprete la tecla Esc para salir");
			Ring();
			Apagar();
				break;

		case '9': system("clear");
			printf("Elegiste Tenista\n");
			printf("\n Aprete la tecla Esc para salir");
			Tenista();
			Apagar();
				break;

		case 'a': system("clear");
			printf("Elegiste Serpiente\n");
			printf("\n Aprete la tecla Esc para salir");
			Serpiente();
			Apagar();
				break;
			
		case 'b': system("clear");
			printf("Adios\n");
				break;
		
		
		default: break;
		
		}
}
return 0;	
}

