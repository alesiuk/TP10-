/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ports.h
 * Author: valentino
 *
 * Created on 28 de octubre de 2020, 14:40
 */

#ifndef PORTS_H
#define PORTS_H

#include <stdio.h>
#include <stdint.h>
/*ESTRUCTURAS*/

typedef struct{       //estructura generica bit a bit de un puerto de 8 bits
    uint8_t b0 :1;
    uint8_t b1 :1;
    uint8_t b2 :1;
    uint8_t b3 :1;
    uint8_t b4 :1;
    uint8_t b5 :1;
    uint8_t b6 :1;
    uint8_t b7 :1;
}bits_t;

typedef union{
    bits_t bits;
    uint8_t byte;
}byte_t;

typedef struct{
    byte_t PortB; //acceso a la parte baja del puerto D
    byte_t PortA; //acceso a la parte alta del puerto D
}puertos_t; //acceso a al puerto D a nivel word

typedef union{
    uint16_t PortD;
    puertos_t puertAB;
}porst_t;



/*FUNCIONES*/

void bitSet (int data, char puerto);        //pone en 1 un bit de un puerto determinado
void bitClr (int data, char puerto);        //pone en 0 un bit de un puerto determinado
void bitToggle (int data, char puerto);    //Conmuta el valor de un bit de un puerto determinado
int bitGet (int data, char puerto);            //Obtiene el valor de un bit. Devuelve dicho valor si no hubo errores, o -1 si hubo un error
void maskOn (int data, char puerto);        //Enciende todos los bits de un puerto segun los bits seteados de una mascara
void maskOff (int data, char puerto);        //Apaga todos los bits de un puerto segun los bits seteados de una mascara
void maskToggle (int data, char puerto);    //Conmuta todos los bits de un puerto segun los bits seteados de una mascara
uint16_t r_port (void);
int potencia(int x,int n);
unsigned int r_portA (void);				//lee el puerto A





#endif          //PORTS_H
