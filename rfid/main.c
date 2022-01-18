
#include <stdio.h>
#include <stdlib.h>		//memoria dinamica
#include <ctype.h>		//toupper
#include <string.h>		//para las funciones de comparacion
#include <time.h>		//para manejar la hora
#include <termios.h>	//para configurar el puerto	
#include <fcntl.h>		//para open
#include <unistd.h>     //para read y write

#define N 30

struct usuario
{
	char nombre[N];
	char apellido[N];
	short int piso;
	char departamento;
	char id[6];                  /*5 digitos mas el final de cadena*/
	char fecha_creacion[N];
	struct usuario *siguiente;
	
};

typedef struct usuario usuario_t;

int iniciar_puerto(void);
void configurar_puerto( int fd);

void configurar_teclado( void );
void restaurar_teclado( void );

void cargar_datos(void);
void menu_config(void);

void escaner(int fd);
void guardar_acceso( FILE *archivo, usuario_t *aux );

void crear_usuario(void);
int leer_archivo(FILE *archivo, char *cadena);

int comprobar_cadena( char *cadena );
void convertir_mayusculas( char *cadena );

int buscar_coincidencia( usuario_t *nuevo);

void guardar_nombre( char *nombre );
void guardar_apellido( char *apellido );
void guardar_piso( short int *piso );
void guardar_departamento( char *departamento );

void guardar_id( usuario_t *nuevo );
void guardar_fecha( usuario_t *nuevo );
void enlazar_nodos( usuario_t *nuevo );
void guardar_archivo_usuarios( usuario_t *nuevo );

void borrar_usuario(void);
usuario_t *buscar_usuario(int opc);
void guardar_archivo_completo( void );

void listar_usuarios(void);

void registro_acceso(void);

usuario_t *primero=NULL;
usuario_t *ultimo=NULL;

struct termios teclado_estandar, teclado_modificado;

int FD;		//agrego esta variable porque no se como pasarle el file descriptor a la funcion guardar id, que esta dentro de crear usuario,
				//que esta adentro de menu_config, sino la tengo que psar como 4 veces al vicio. Si se les ocurre una forma cambienlo.
int main(void)
{
	int fd, opc;
	
	fd = iniciar_puerto();
	
	cargar_datos();
	
	while(1)
	{
		system( "clear" );
		printf("----------MENU PRINCIPAL----------\n\n");
		printf("1 - Modo escaneo\n"); 
		printf("2 - Configuraciones\n");
		printf("3 - Salir\n\n");
		
		printf("Seleccione una opcion: ");
		scanf("%d", &opc);
		
		switch(opc)
		{
			case 1: escaner(fd);
					break;
			
			case 2: menu_config();
					break;
					
			case 3: return 0;
					break;
			
			default: system( "clear" );
					 printf("Error: Opción invalida. Por favor, intente otra vez. ");
					 getchar();
					 getchar();
					 break;
		}
	  
	 }
	
}

int iniciar_puerto(void)
{													//Segun Treviño esta en /dev/ttyUSB0 pero eso no existe en mi pc, cuando conecto un
	char puerto[] = "/dev/ttyS0";			 //pendrive me aparece en /dev/sdc1 pero supuestamente cuando conectemos el adaptador
	int fd;																		// USB-RS232 deberia salir en donde dice Trevi	
	
	fd = open( puerto, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK );        
	
	if( fd == -1)				//si no pudo abrir el puerto salimos, porque no podemos hacer nada. Podriamos cambiarlo para que no salga y deje hacer configuraciones pero sin escanear
	{
		printf("Error Fatal: No se pudo abrir el puerto. ");
		exit( -1 );
	}
	
	configurar_puerto( fd );
	
	FD = fd;    //guardamos en la variable global FD
	
	return fd;
}

void configurar_puerto( int fd )
{
	struct termios config;
	
	fcntl(fd, F_SETFL, FNDELAY); //para mi esto es redundante, porque ya le ponemos NDELAY cuando lo abrimos, pero en el codigo de Trevi 
									//estaba, asique lo dejo por las dudas. De ultima despues lo comentamos/borramos
	
	cfsetispeed( &config, B9600);  //si hace falta le ponemos mas velocidad

	config.c_cflag |= (CLOCAL | CREAD); //esto es para poder leer el puerto y no darle bola al handshaking con el modem
	
	config.c_cflag &= ~CSIZE;	//ponemos en 0 todos los bits correspondientes al tamaño
	config.c_cflag |= CS8;		//ponemos en 1 los bits correspondientes a 8 
	
	config.c_cflag &= ~PARENB; //ponemos en 0 los bits correspondientes a la paridad (no paridad)
	
	config.c_cflag &= ~CSTOPB; //ponemos en 0 el bit de stop (1 bit de stop)
	
	config.c_lflag &= ~(ECHO | ICANON | ISIG); //desactivamos modo canonico
	config.c_oflag &= ~OPOST;
	
	config.c_cc[VTIME] = 0;			//para que no espere ni un determinado tiempo ni una cantidad minima de caracteres al leer
	config.c_cc[VMIN] = 0;

	tcsetattr( fd, TCSANOW, &config );	//para pasarle la config de la estructura termios al puerto
	
}

void configurar_teclado( void )
{
	tcgetattr(0, &teclado_estandar);			 //guardamos la configuracion vieja de stdin (teclado/ fd=0) para volverlo a la normalidad 
												 //cuando terminemos	
	teclado_modificado = teclado_estandar;
	
	teclado_modificado.c_lflag &= ~ICANON;		//modo no canonico
	teclado_modificado.c_lflag &= ~ECHO;
	teclado_modificado.c_lflag &= ~ISIG;
	
	teclado_modificado.c_cc[VMIN] = 0;			//para que no espere al leer
	teclado_modificado.c_cc[VTIME] = 0;
	
	tcsetattr(0, TCSANOW, &teclado_modificado);	//para setearlo	
}

void restaurar_teclado( void ) 
{
	tcsetattr(0, TCSANOW, &teclado_estandar);	//dejamos el teclado como estaba
}


void cargar_datos(void)		
{							
	usuario_t *aux;
	FILE *archivo;
	char cadena[N];
	int estado;
	
	archivo = fopen("Usuarios.txt", "r");
	
	if(archivo == NULL)
	{
		printf("No se encontraron datos anteriores. ");
		getchar(); 
		return;
	}
	
	primero = (usuario_t *) malloc( sizeof( usuario_t ) ); /*reserva de lugar en memoria*/
	
	if( primero == NULL )
	{
		printf("Error: No se pudo cargar los datos. No hay memoria suficiente. ");
		getchar();
		return;
	}
	
	estado = leer_archivo( archivo, primero->nombre ); //el EOF tiene que estar en la primera letra del nombre
	
	if( estado == -1)
	{
		printf("No se encontraron datos anteriores.\n");
		getchar();
		primero=NULL; 
		return;
	}
		
	leer_archivo( archivo, primero->apellido);
		
	leer_archivo( archivo, cadena );
	primero->piso = atoi( cadena );
		
	primero->departamento = fgetc( archivo );
	fgetc( archivo );                                       //para el ;
		
	leer_archivo( archivo, primero->id);
		
	leer_archivo( archivo, primero->fecha_creacion);
				
	ultimo = primero;
	ultimo->siguiente = NULL;
	
	while( 1 )
	{
		aux = (usuario_t *) malloc( sizeof( usuario_t ) );
	
		if(aux == NULL)
		{
			system( "clear" );
			printf("Error: No hay suficiente memoria para almacenar los datos\n");
			getchar();
			fclose( archivo );
			return;
		}
		
		estado = leer_archivo( archivo, aux->nombre );
		
		if(estado == -1)	//si encontro EOF, cierra el archivo y sale
		{
			fclose( archivo );
			return;
		}
			
		leer_archivo( archivo, aux->apellido );
				
		leer_archivo( archivo, cadena );
		aux->piso = atoi( cadena );
				
		aux->departamento = fgetc( archivo );
		fgetc( archivo );                                       //para el ;
				
		leer_archivo( archivo, aux->id);
				
		leer_archivo( archivo, aux->fecha_creacion);
				
		ultimo->siguiente = aux;
		ultimo = aux;
		ultimo->siguiente = NULL;
		
	}
	
		
}

int leer_archivo(FILE *archivo, char *cadena)
{
	int i;
		
	for( i=0 ; i<N ; i++) /*30 es el limite de la cadena pero lo podemos cambiar*/
	{
		cadena[i] = fgetc( archivo );     /*vamos leyendo de a 1 caracter y lo guardamos en la cadena*/
		
		if( cadena[i] == EOF )  
			return -1;
			
		if( cadena[i] == ';')       /*usamos el ; para separar las cosas cuando guardamos el archivo*/ 
		{
			cadena[i] = '\0';	/*si encuentra un ; pone un \0 para indicar que termina la cadena y sale del for*/
			break;
		}
	}
	
	return 0;
}

void menu_config(void)
{
	int opc;
	
	while(1)
	{
		system("clear");
		printf("---------- Menu de configuraciones ----------\n\n");
		printf("1 - Crear nuevo usuario\n");
		printf("2 - Borrar un usuario existente\n");
		printf("3 - Ver lista de usuarios\n");
		printf("4 - Ver registro de acceso\n");
		printf("5 - Volver\n");
	
		printf("\nIngrese una opcion: ");
		scanf(" %d", &opc);
	
		switch(opc)
		{	
			case 1: crear_usuario();
					break;
				
			case 2: borrar_usuario();
					break;
				
			case 3: listar_usuarios();
					break;
				
			case 4: registro_acceso();
					break;
			
			case 5: return;
					break;
				
			default:
					system("clear");
					printf("Error: Opción no valida. Por favor, intente otra vez.");
					getchar();																/*enter suelto*/
					getchar();														/*para que espere antes de limpiar la pantalla*/
					break;
		}
	}
}


void crear_usuario(void)
{
	usuario_t *nuevo;
		
	system( "clear" );
	
	nuevo = (usuario_t *) malloc( sizeof( usuario_t ) ); /*reserva de lugar en memoria*/
	
	if( nuevo == NULL )
	{
		printf("Error: No se pudo crear el usuario. No hay memoria suficiente");
		getchar();
		return;
	}
		
	getchar();								//enter suelto					
		
	guardar_apellido( nuevo->apellido );
	convertir_mayusculas( nuevo->apellido );	/*para que la busqueda sea mas facil*/
	
	guardar_nombre( nuevo->nombre );	
	convertir_mayusculas( nuevo->nombre );
	
	guardar_piso( &(nuevo->piso) );	
	getchar();       						//enter suelto
	
	guardar_departamento( &(nuevo->departamento) );	
		
	if( buscar_coincidencia(nuevo) != 0)   //buscar coincidencia devuelve el numero de usuarios con los mismos datos. Igual, por
	{										//la forma en que esta hecho, no deberia encontrar mas de uno
		system( "clear" );
		printf("El usuario ya existe! ");
		getchar();
		getchar();
		free( nuevo );	
		return;
	}
	
	
	printf("\nPresente la tarjeta o llavero... ");
	
	guardar_id( nuevo );
	
	guardar_fecha( nuevo );  
	
	enlazar_nodos( nuevo );
	
	guardar_archivo_usuarios( nuevo );
		
}

void guardar_apellido( char *apellido )
{
	int valido=0;
	
	do{
		  system( "clear" );
			
		  printf("Apellido: ");
		  gets( apellido ); 
		
		  valido = comprobar_cadena( apellido );
			
		  if( valido != 1)
		  {
			  printf("\nError: se han introducido caracteres invalidos. Solo se permiten mayusculas y minusculas. ");
			  getchar();	//para que espere antes de repetir
		  }
		  
	  }while( valido != 1);
}

void guardar_nombre( char *nombre)
{
	int valido = 0;
	
	do{
		  printf("Nombre: ");
		  gets( nombre );
	
		  valido = comprobar_cadena( nombre );
			
		  if( valido != 1)
		  {
			  printf("\nError: se han introducido caracteres invalidos. Solo se permiten mayusculas y minusculas. ");
			  getchar();	//para que espere antes de repetir
			  system( "clear" );
		  }
	  
	  }while( valido != 1);
}

void guardar_piso( short int *piso )
{
	do{																
		printf("Piso: ");
		scanf(" %hd", piso );
		
		if( *piso < 0 || *piso > 50 )					//lo de 0 y 50 lo puse al azar, podemos agregar otra opcion en el menu
		{																//de configuraciones que permita elegir el numero de pisos		
			printf("\nError: El piso debe estar entre 0 y 50. ");
			getchar();	
			getchar();	//para que espere antes de repetir
			system( "clear" );
		}
		
	   }while( *piso < 0 || *piso > 50);
}

void guardar_departamento( char *departamento)
{
	do{
		printf("Departamento: ");
		*departamento = getchar();
		*departamento = toupper( *departamento );
		
		if( *departamento < 'A' || *departamento > 'Z')	   //si agregamos la opcion de configurar edificio, podemos cambiar esto
		{
			printf("\nError: El departamento debe ser una letra entre \"a\" y \"z\". ");
			getchar();
			getchar();	//para que espere antes de repetir
			system( "clear" );
		}	
	
	  }while( *departamento < 'A' || *departamento > 'Z');
}

void guardar_archivo_usuarios( usuario_t *nuevo )
{
	FILE *archivo;
	
	archivo = fopen("Usuarios.txt", "a"); /*modo "a" para que no se sobreescriba*/
		
	if( archivo == NULL)
		printf("\n\nAdvertencia: Hubo un error al abrir el archivo, el usuario que agrego no estará disponible una vez que cierre el programa.\n\n");
	else
	{
		fprintf( archivo, "%s;%s;%hd;%c;%s;%s;", nuevo->nombre, nuevo->apellido, nuevo->piso, nuevo->departamento, nuevo->id, nuevo->fecha_creacion);
		fclose(archivo);
	}

}

void enlazar_nodos( usuario_t *nuevo )
{
	if( primero == NULL )   /*la lista esta vacia, estamos agregando al primer usuario*/
	{
		primero = ultimo = nuevo;
		primero->siguiente=NULL;
	}
	else
	{
		ultimo->siguiente = nuevo;		/*enlazamos los nodos*/
		ultimo = nuevo;					/*movemos el ultimo*/
		ultimo->siguiente = NULL;		/*marcamos el final de la lista*/
	}
}

void guardar_id( usuario_t *nuevo )
{
	int i=0, leido;
	char letra=0;
	
	printf("\n");
	
	
	do{
		leido = read( FD, &letra, 1); 		//leemos 1 char del puerto y lo guardamos en letra
		
		if( leido > 0 && letra == 'a')					//si leemos una a 
		{

			for( i = 0 ; i < 5 ; i++)
				read( FD, &( nuevo->id[i] ), 1);	//leemos los caracteres, porque cuando empiece a mandar va a seguir mandando	 
 		
			nuevo->id[5] = '\0';		//colocamos el final de cadena (para imprimirlo mas facil)
		}
		
	  }while (i < 5);		//cuando i=5 ya leyo todo 

	printf("\n");
	
	write( FD, "v", 1); 
}
	
int comprobar_cadena( char *cadena )
{
	int i=0;
	
	while( cadena[i] ) //mientras no lleguemos al final
		if( (cadena[i] >= 'a' && cadena[i] <= 'z') || (cadena[i] >= 'A' && cadena[i] <= 'Z') ) //si la letra esta entre a y z o entre A y Z
			i++;																			//se fija en el caracter siguiente
		else                      //sino, devuelve error                                      
			return -1;
	
	return 1;	//si llego hasta el final sin salir, la cadena es valida
}

int buscar_coincidencia( usuario_t *nuevo)
{
	int conc = 0;
	usuario_t *aux = primero;
	
	while( aux != NULL)
	{
		if( strcmp( aux->apellido , nuevo->apellido ) == 0)
			if( strcmp( aux->nombre , nuevo->nombre ) == 0)
				if( aux->piso == nuevo->piso )
					if( aux->departamento == nuevo->departamento )
						conc++;
	
		aux = aux->siguiente;
	}
	
	return conc;
}					
		
void convertir_mayusculas( char *cadena )
{
	int i;
	
		for( i=0 ; cadena[i] ; i++)		/*vamos pasando cada caracter*/
			if ( cadena[i] >= 'a' && cadena[i] <= 'z' )	/*si es una letra minuscula*/
				cadena[i] -= 32;  /*le restamos 32 para que quede mayuscula*/
}

void guardar_fecha( usuario_t *nuevo)
{
	struct tm *fecha_estructura;
	time_t fecha_t;
	char fecha[N];
	
	fecha_t = time(0);																
	fecha_estructura = localtime( &fecha_t );      									
	strftime(fecha, sizeof(fecha), "%a %Y-%m-%d %H:%M:%S %Z", fecha_estructura);
		
	strcpy( nuevo->fecha_creacion, fecha);
}

void borrar_usuario(void)
{
	usuario_t *aux, *encontrado;
	int opc;
	
	system ( "clear" );
	
	if( primero == NULL)    /*si la lista esta vacia*/
	{
		printf("Error: No hay usuarios que borrar. ");
		getchar();
		getchar();
		return;
	}
	
	do
	{
		system ( "clear" );
		
		printf("----------Opciones de borrado----------\n\n");
		printf("1 - Buscar por nombre y apellido\n");
		printf("2 - Buscar por piso y departamento\n");
	
		printf("\nSeleccione una opcion: ");
		scanf(" %d", &opc);
	
		getchar(); //Enter suelto
				
		if(opc < 1 || opc > 2)
		{
			system("clear");
			printf("Error: Opción no valida. Por favor, intente otra vez. ");
			getchar();																/*para que espere antes de limpiar*/
		}										
	
	}while(opc < 1 || opc > 2);
	
	encontrado = buscar_usuario(opc); //buscar usuario devuelve un puntero a la estructura del usuario
		
	if( encontrado == NULL)      /*No encontro el usuario*/
	{
		system( "clear" );
		printf("Error: El usuario no existe. ");
		getchar();
		return;
	}
		
	if( encontrado == primero)
	{
		primero = primero->siguiente;
		free( encontrado );
	}
		
	else
	{
		aux = primero;     /*empezamos del principio de la lista*/
			
		while ( aux->siguiente != encontrado)    /*buscamos el anterior al que tenemos que borrar*/
			aux = aux->siguiente;	

		if( aux->siguiente == ultimo) 		/*si justo el que vamos a borrar es el ultimo, tenemos que mover el puntero*/
			ultimo = aux;					/*para que no haya errores despues cuando agreguemos otro usuario*/
			
		aux->siguiente = encontrado->siguiente;    /*acomodamos los punteros*/
		free( encontrado );		
		
	}
		
	guardar_archivo_completo();
			
	
}

usuario_t *buscar_usuario(int opc)
{
	char apellido[20];
	char nombre[20];
	short int piso;
	char departamento;
	usuario_t *aux, *encontrado;  /*encontrado por si es uno solo*/
	int conc=0;
	
	system( "clear" );
		
	aux=primero;
	
	if(opc == 1)
	{
		guardar_apellido( apellido );
		convertir_mayusculas( apellido );
		
		guardar_nombre( nombre );
		convertir_mayusculas( nombre );
		
		while(aux != NULL)
		{
			if( strcmp( aux->apellido , apellido ) == 0)
				if( strcmp( aux->nombre , nombre ) == 0)
				{
					conc++;				
					encontrado = aux;         /*si encuentra mas de uno, va a guardar el ultimo, pero no importa porque no lo vamos a usar*/
				}
            		
			aux = aux->siguiente;
		}

		if(conc == 0)
			return NULL;
		
		if(conc == 1)
			return encontrado;	
		
		else                             /*si hay mas de 1 usuario con el mismo nombre, por ejemplo si alguien alquila 2 dptos*/
		{
			system( "clear" );
			printf("Al parecer hay mas de un usuario con ese nombre\n\n");
			
			guardar_piso( &piso );
			getchar();       						//enter suelto
		
			guardar_departamento( &departamento);	//ahora tenemos todos los datos. Por la forma en que esta hecha la creacion
			
			getchar();
													//	no puede haber dos usuarios que tengan exactamente los mismos datos, asique el
			aux = primero;							   //primero que coincida va a ser el que buscamos
														
			while( aux != NULL)
			{
				if( strcmp( aux->apellido , apellido ) == 0)
					if( strcmp( aux->nombre , nombre ) == 0)
						if( aux->piso == piso )
							if( aux->departamento == departamento )
								return aux;
												
				aux = aux -> siguiente;
			}
			
			return NULL; /*si sale del bucle sin devolver aux, significa que no encontro al usuario, o sea, si hay usuarios con ese
							nombre, pero no en el piso y departamento que ingresaron*/
		}
	}

if(opc == 2)
	{
		guardar_piso( &piso );
			
		getchar();       									//enter suelto
		
		guardar_departamento( &departamento );
		
		getchar();
				
		while(aux != NULL)
		{
			if( aux->piso == piso)
				if( aux->departamento == departamento )
				{
					conc++;				
					encontrado = aux;         /*si encuentra mas de uno, va a guardar el ultimo, pero no importa porque no lo vamos a usar*/
				}
            		
			aux = aux->siguiente;
		}

		if(conc == 0)
			return NULL;
			
		if(conc == 1)
			return encontrado;
		
		else
		{
			system( "clear" );
			printf("Al parecer hay mas de un usuario que vive en ese departamento. ");		//POR ALGUNA RAZON NO IMPRIME ESTO
			getchar();
						
			guardar_apellido( apellido );
			convertir_mayusculas( apellido );
		
			guardar_nombre( nombre );
			convertir_mayusculas( nombre );
			
			//ahora tenemos todos los datos. Por la forma en que esta hecha la creacion no puede haber dos usuarios que tengan exactamente
			// los mismos datos, asique el primero que coincida va a ser el que buscamos
			
			aux = primero;							   
														
			while( aux != NULL)
			{
				if( strcmp( aux->apellido , apellido ) == 0)
					if( strcmp( aux->nombre , nombre ) == 0)
						if( aux->piso == piso )
							if( aux->departamento == departamento )
								return aux;
												
				aux = aux -> siguiente;
			}
			
			return NULL; /*si sale del bucle sin devolver aux, significa que no encontro al usuario, o sea, si hay usuarios con ese
							nombre, pero no en el piso y departamento que ingresaron*/
		}		
	}
}

void guardar_archivo_completo( void ) //podemos cambiar esta funcion para que llame a la funcion guardar_archivo_usuarios repetidamente
{										//y asi reutilizar mas codigo, pero hay que modificar la otra tambien y hay que ver como	
	FILE *archivo;						//hacemos con los modos de apertura (w y a) 
	usuario_t *aux;
	
	archivo = fopen("Usuarios.txt", "w"); /*modo w para que escriba todo el archivo de nuevo*/				
		
		if( archivo == NULL)
			printf("Advertencia: Hubo un error al abrir el archivo, el usuario que eliminó estará disponible cuando vuelva a abrir el programa.\n\n");
		else
		{
			aux = primero;
			
			while(aux != NULL)
			{
				fprintf( archivo, "%s;%s;%hd;%c;%s;%s;", aux->nombre, aux->apellido, aux->piso, aux->departamento, aux->id, aux->fecha_creacion);
				aux = aux->siguiente;
			}			
		
			fclose(archivo);
		}
}	

void listar_usuarios(void)		/*ES UNA FUNCION BASTANTE BASICA, DESPUES SI QUIEREN PODEMOS PENSAR/BUSCAR UN ALGORITMO DE ORDENAMIENTO*/
{								/* PARA MOSTRAR LOS USUARIOS ORDENADOS ALFABETICAMENTE, POR PISO, POR DEPARTAMENTO, ETC. COMO PARA */
	usuario_t *aux=primero;		  /*AGREGARLE ALGO, AUNQUE ES MEDIO ENQUILOMBADO PORQUE VA A CAMBIAR TODA LA FORMA DE LA LISTA*/
		
	system( "clear" );
	
	if( primero == NULL)
	{
		printf("Error: No hay usuarios registrados. ");
		getchar();
		getchar();
		return;
	}
	
	printf("------------------------------------USUARIOS REGISTRADOS------------------------------------");    /*P A R A C H E   S T Y L E*/
	printf("\n\n");
	printf("Fecha de creacion             Apellido            Nombre              Piso      Departamento\n\n");
	
	while( aux != NULL)
	{	
		printf("%-30s%-20s%-20s%.2hd        %c\n", aux->fecha_creacion, aux->apellido, aux->nombre, aux->piso, aux->departamento);
		
		aux = aux->siguiente;																			
	}
	
	getchar(); //para que espere antes de volver al main
	getchar();
}

void escaner(int fd) 
{
	usuario_t *aux = primero;
	char id[6];          /*5 digitos + final de cadena*/
	FILE *archivo;
	int leido = 0, i;
	char letra = 0;
	
	system( "clear" );	
	
	if ( primero == NULL)	//si entra en modo escaneo sin crear un usuario no va a poder abrir la puerta porque no tenemos el id
	{
		printf("Error: No hay ningun usuario registrado. Cree un usuario nuevo y luego vuelva a intentar. ");
		getchar();
		getchar();
		return;
	}
																							
	archivo = fopen("Acceso.txt", "a");    //Abro este archivo para guardar	la fecha y el id de los usuarios modo "a" para que no se 
											//sobreescriba
	if( archivo == NULL)
		printf("Advertencia: Hubo un error al abrir el archivo de acceso, las personas que entren o salgan no serán registradas.\n\n");
		
	configurar_teclado();
	
	getchar();
	printf("Escaneando... (Pulse ESC para salir)\n\n");
	getchar();
			 
	do{
		leido = read( fd, &letra, 1); 		//leemos 1 char del puerto y lo guardamos en letra
		
		if( leido > 0 && letra == 'a' )					//si efectivamente leyo algo 
		{
			for( i = 0 ; i < 5 ; i++)
				read( fd, &id[i], 1);	//leemos los 6 restantes caracteres, porque cuando empiece a mandar va a seguir mandando	 
 		
			id[5] = '\0';		//colocamos el final de cadena (para imprimirlo mas facil)
			
			aux = primero;
			
			while( aux != NULL)		//mientras haya lista comparamos los id que tenemos guardados en la lista con el que nos llego
			{
									
				if( strcmp( aux->id , id ) == 0 )      //si encontramos el id en los guardados
				{
					write( fd, "o", 1);  		//mandamos al puerto una o (open)
							
					printf("Acceso concedido\n");
					
					guardar_acceso( archivo, aux );
			
					break; //salimos del while porque ya encontramos al usuario que entro o salio*/
				}
				
				aux = aux->siguiente;	//seguimos buscando	
			}
								//si aux es null significa que recorrió toda la lista hasta el final y no salio con el break, es decir que no
			if( aux == NULL)    		//encontro un usuario con esa id, asique mandamos al puerto una n (no valido / no encontrado)
			{
				write( fd, "n", 1);
				printf("Error: ID invalido. Acceso denegado.\n") ;
			}
		}
		
		read( 0, &letra, 1); 	//leemos un caracter del teclado y lo guardamos en letra
		
	}while( letra != 27 ); 	//Ascii 27 = ESC
	
	restaurar_teclado();
	
	fclose(archivo);

}

void guardar_acceso( FILE *archivo, usuario_t *aux )
{
	time_t fecha_acceso;
	struct tm *fecha_estructura;
	char fecha[N];
		
	if( archivo != NULL)			/*si pudimos abrir el archivo*/
	{
		fecha_acceso = time(0);
		fecha_estructura = localtime( &fecha_acceso );      
		strftime(fecha, sizeof(fecha), "%a %Y-%m-%d %H:%M:%S %Z", fecha_estructura);
			
		fprintf( archivo , "%s;%s;%s;", fecha, aux->apellido, aux->nombre);  /*guardamos los datos del usuario y la fecha en que accedio*/  
	}
}	

void registro_acceso(void)
{
	char fecha[N], apellido[N], nombre[N];
	int estado;
	FILE *archivo;
	
	system( "clear" );
	
	archivo = fopen("Acceso.txt", "r");    
	
	if( archivo == NULL)
	{
		printf("Error: No se pudo abrir el archivo de acceso. ");
		getchar();					
		getchar();			
		return;
	}

	
	printf("-------------------------------REGISTRO DE ACCESO-------------------------------");    /*P A R A C H E   S T Y L E*/
	printf("\n\n");
	printf("Fecha                         Usuario\n\n");
	
	while( 1 )
	{
		estado = leer_archivo( archivo, fecha );

		if( estado == -1)		/*si encontro el final del archivo ya imprimimos todo y hay que salir*/
			break;

		leer_archivo( archivo, apellido );
		
		leer_archivo( archivo, nombre );
				
		printf("%-30s%s, %s\n", fecha, apellido, nombre); 
	}
	
	getchar();
	getchar();
	
	fclose( archivo);
	
}
	
