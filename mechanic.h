/*

MODURALIZACION: Se encarga de la interfaz, entre la maquina y el usuario.

FUNCIONES

------input: Esta funcion se encarga del input y de su verificacion, no recibe nada y agarra con getchar los datos ingresado por el usuario para ver si son correctos, si lo son devuelve el caracter (si es letra entonces lo devuele en minuscula) si no son validos entoces vuelve a arrancar.
------pregunta: funcion que devuelve el char correspodiente si es que se apreto si (Y) o no (N). Si ingreso uno incorrecto entonces vuelve a preguntar. No devuelve nada.
*/


#ifndef MECHANIC_H
#define MECHANIC_H

#include <stdio.h>
#include <stdint.h>

#define ASCII 48


void print_portA(unsigned int);			//funcion que imprime el estado del puerto A. No devuelve nada, resive el valor del puerto A


void sw (char);					//Esta funicon recibe que boton se apreto y no devuelve nada. Se encarga de cambiar los estados de los leds segun indique el usuario

#endif		//INPUT_H



