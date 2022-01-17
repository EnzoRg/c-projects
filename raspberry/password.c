#include "funciones.h"

int password()
{
	int pos = 0;
	char ch;
	char clave[]="perro";
	char entrada[N];
	int i;
	struct termios t_old, t_new;

	tcgetattr(FD_STDIN, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(FD_STDIN, TCSANOW, &t_new);
	
	printf("Tecnicas Digitales II\n");
		
	for(i=0; i<INTENTOS; i++)
	{
		printf("Ingrese su clave de 5 digitos:\n");
		while(1)
		{
			ch=getchar();
			if(ch == ENTER)
			{	
				pos = 0;
				break;
			}
			else
			{
				printf("*");
				entrada[pos++] = ch;
				entrada[pos] = '\0';
			}
		}
		if(!strcmp(clave, entrada))
		{
			system("clear");
			tcsetattr(FD_STDIN, TCSANOW, &t_old);
			break;
		}		
		system("clear");
		printf("Clave no valida!\n");
		if(i == INTENTOS-1)
			{
				printf("Supero los %d intentos.\n", INTENTOS);
				tcsetattr(FD_STDIN, TCSANOW, &t_old);
				return 0;
			}
	}	
	tcsetattr(FD_STDIN, TCSANOW, &t_old);
	return 1;
}
