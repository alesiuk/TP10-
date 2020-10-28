
/*

	Bienvenidos al programa de los leds del Grupo 5.
Este programa se encarga de jugar con 8 leds que son manejados por el usuario.
Usando la libreria hecha en el ejercicio 4 podemos jugar con el puerto A prendiendo y apagando los leds.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "input.h"
#include "mechanic.h"
#include "ports.h"

void bienvenida();


int main (void)
{

	int mientras=1;							//inicializo variable que utilizo para un while

	bienvenida();							//le doy la bienvenida al usuario

	print_portA(0);							//imprimo el estado inicial del puerto A, es decir, todos los leds apagados
	
	while (mientras)						//este while esta para ver si se apreta la q, si se apreta entonces sale del while y termina el programa
	{
		printf("Presione la tecla que desee usar: \n");
		char dato;
		dato = input();						//guardo en dato lo que ingreso el usuario por interfaz
		if(dato == 'q')
		{															//si es q entonce entro
            printf("Estas seguro que quieres salir? (Y/N)\n");				//le pregunto al usuario si esta seguro que quiere salir
			char seg = pregunta();									//agarro la respuesta en la variable seg
			if ((seg=='y') || (seg=='Y'))							//si pone si entonces lo termino
			{
				mientras=0;
				continue;
			}														//si no pone 'n' entonces tranqui, segui con el programa
		}					
		sw(dato);													//cambio el estado de los leds tal cual como ordeno el usuario
		unsigned char r = r_portA();								//leeo el estado del puerto A
		print_portA(r);												//Lo imprimo en pantalla
	}
	return 0;
}




void bienvenida ()					//funcion que le da la bienvenida al usuario
{
    printf("Bienvenidos al TP 10 del grupo 5 \n");
    printf("Este programa es un simulador de 8 LEDs conectados al puerto A, cada LED representa un bit del puerto.\n");
    printf("Este programa permite modificar cada LED del puerto mediante las siguientes instrucciones:\n");
    printf(" Para prender un LED especifico presione un numero del 0 al 7.\n");
    printf(" Para cambiar todos los LEDs al estado opuesto presione la tecla 't'.\n");
    printf(" Para apagar todos los leds presione la tecla 'c'.\n");
    printf(" Para prender todos los leds presione la tecla 's'.\n");
    printf(" Para finalizar el programa presione la tecla 'q'.\n");
}
