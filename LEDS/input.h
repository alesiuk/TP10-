/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input.h
 * Author: valentino
 *
 * Created on 28 de octubre de 2020, 14:47
 */


/*

MODURALIZACION: Se encarga de la interfaz, entre la maquina y el usuario.

FUNCIONES

------input: Esta funcion se encarga del input y de su verificacion, no recibe nada y agarra con getchar los datos ingresado por el usuario para ver si son correctos, si lo son devuelve el caracter (si es letra entonces lo devuele en minuscula) si no son validos entoces vuelve a arrancar.
------pregunta: funcion que devuelve el char correspodiente si es que se apreto si (Y) o no (N). Si ingreso uno incorrecto entonces vuelve a preguntar. No devuelve nada.
*/


#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdint.h>

#define ASC 32


char input (void);					//Esta funcion se encarga del input y de su verificacion, no recibe nada y agarra con getchar los datos ingresado por el usuario para ver si son correctos, si lo son devuelve el caracter (si es letra entonces lo devuele en minuscula) si no son validos entoces vuelve a arrancar.


char pregunta (void);				//funcion que devuelve el char correspodiente si es que se apreto si (Y) o no (N). Si ingreso uno incorrecto entonces vuelve a preguntar. No devuelve nada.

#endif		//INPUT_H
