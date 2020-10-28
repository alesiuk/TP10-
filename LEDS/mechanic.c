/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/*
MODURALIZACION: Parte mecanica que se encarga de las funciones que cambian los estados de los leds, imprimen el estado del puerto A y cual es.

FUNCIONES
------sw : Esta funicon recibe que boton se apreto y no devuelve nada. Se encarga de cambiar los estados de los leds segun indique el usuario
------print_portA : funcion que imprime el estado del puerto A. No devuelve nada, resive el valor del puerto A
*/


#include <stdio.h>
#include <stdint.h>
#include "mechanic.h"
#include "ports.h"


void print_portA(unsigned int PortA){				//funcion que imprime el estado del puerto A. No devuelve nada, resive el valor del puerto A
	printf("PortA:\n");
	for(int8_t i = 40; i > 0; i--){		
		printf("-");					
	}									 
	printf("\n");
	printf("|    b7  b6  b5  b4  b3  b2  b1  b0    |\n");
	printf("|    ");
	for(int8_t i = 7; i >= 0; i--){			//Recorro cada bit individualmente y me fijo si termina en 1
		printf("%c   ", (PortA >> i) % 2 ? '*' : ' ' );
	}
	printf("  |\n");
	for(int8_t i = 40; i > 0; i--){
		printf("-");
	} 
	printf("\n");
	return;
}

void sw (char insta)			//Esta funicon recibe que boton se apreto y no devuelve nada. Se encarga de cambiar los estados de los leds segun indique el usuario
{
	switch (insta)
	{
		case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': 		//si es un numero entonces prendo ese bit con la funcion bitSet
		bitSet((insta-ASCII),'a');
		break;
		case 't' : 
		for(int i=0 ; i<8;i++)						//si apreto la t entonces cambia todos los estados de los led al opuesto con bitToggle
		{
			bitToggle(i,'a');
		}
		break;
		case 's':									//si apreto la s entonces se prendieron todos los leds usando bitSet
		for(int i=0 ; i<8;i++)
		{
			bitSet(i,'a');
		}
		break;
		case 'c':									//si apreto la c entonces se apagan todos los leds usando bitClr
		for(int i=0 ; i<8;i++)
		{
			bitClr(i,'a');
		}
		break;
		default: break;
	}
	return;
}