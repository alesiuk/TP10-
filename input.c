
/*

MODURALIZACION: Se encarga de la interfaz, entre la maquina y el usuario.

FUNCIONES

------input: Esta funcion se encarga del input y de su verificacion, no recibe nada y agarra con getchar los datos ingresado por el usuario para ver si son correctos, si lo son devuelve el caracter (si es letra entonces lo devuele en minuscula) si no son validos entoces vuelve a arrancar.
------pregunta: funcion que devuelve el char correspodiente si es que se apreto si (Y) o no (N). Si ingreso uno incorrecto entonces vuelve a preguntar. No devuelve nada.

*/

#include <stdio.h>
#include "input.h"


char input (void)
{

	int durante = 1;		//variable que va a estar dentro del while hasta que se ingrese un dato correcto
	char resp;				//devuelvo el char que esta ingresado
	char c1, c2;			//variables que guardo los chars ingresados


	while(durante)			//un while hasta que ingrese bien el dato
	{
		c1= getchar();		//agarro el 1er char
		c2= getchar();		//agarro el 2do char
		
		if(c2 == '\n')		//si el segundo es un enter entonces bien
		{
			if( ((c1>='0') && (c1<='7')) || (c1== 't') || (c1=='T') || (c1== 'c') || (c1=='C') || (c1== 's') || (c1=='S') || (c1== 'q') || (c1=='q'))		//si es correcto lo ingresado entonces ok
			{
                if((c1>='A') && (c1<='Z')){		//si lo ingresa en mayuscula, lo pasa a minuscula
				
					c1 += ASC;
				}
				resp= c1;						//si todo es correcto entonces lo guardo en resp
				durante=0;						//y salgo del while
			}
			else								//si no es un caracter valido entonces vuelvo a arrancar
			{
				printf("El caracter ingresado no es valido. Por favor, vuelva a ingresarlo:\n");
			}
		}
		else				//si el segundo char no es un enter entonces hago un refresh y vuelvo al while
		{
			char c;
			while ( (c=getchar()) != '\n')				//refresh.
			{
				c=0;
			}
			printf("El caracter ingresado no es valido. Por favor, vuelva a ingresarlo:\n");
		}
	}
	return resp;
}

char pregunta (void)				//funcion que devuelve el char correspodiente si es que se apreto si (Y) o no (N). Si ingreso uno incorrecto entonces vuelve a preguntar. No devuelve nada.
{
	char res;				//variable donde voy a guardar el char
	int hey =1;				//variable para el while hasta que ponga el char correcto
	char g1,g2;				//variables para getchar

	g1=getchar();
	g2=getchar();

	while(hey)				//un while hasta que el usuario ponga el char correcto
	{
		if(g1 == '\n')		//si es enter entonces error
		{
			printf("El caracter ingresado no es valido. Estas seguro que quieres salir? (Y/N)\n");
		}
		else if (g2 == '\n')													//si el segundo es un enter entonces me fijo el char
		{
			if ((g1=='n') || (g1=='N') || (g1== 'y') || (g1=='Y'))				//si el char es correcto entonces ok
			{
				res=g1;															//guardo el char en res
				hey=0;
			}
			else																//si el char no es correcto entonces error
			{
				printf("El caracter ingresado no es valido. Estas seguro que quieres salir? (Y/N)\n");
			}
		}
		else				//si el segundo char no es un enter entonces hago un refresh y vuelvo al while
		{
			char g;
			while ( (g=getchar()) != '\n')				//refresh.
			{
				g=0;
			}
			printf("El caracter ingresado no es valido. Estas seguro que quieres salir? (Y/N)\n");
		}
	}

	return res;
}






