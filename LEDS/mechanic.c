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


void bienvenida ()					//funcion que le da la bienvenida al usuario
{
    printf("Bienvenidos al TP 10 del grupo 5 \n");
    printf("Este programa es un simulador de 8 LEDs conectados al puerto A, cada LED representa un bit del puerto.\n");
    printf("Este programa permite modificar cada LED del puerto mediante las siguientes instrucciones:\n");
    printf(" Para prender un LED especifico presione un numero del 0 al 7.\n");
    printf(" Para cambiar todos los LEDs al estado opuesto presione la tecla 't'.\n");
    printf(" Para apagar todos los leds presione la tecla 'c'.\n");
    printf(" Para prender todos los leds presione la tecla 's'.\n");
    printf ("Para hacer titilar los leds presione la tecla 'b'. Para pararlos volver a tocar la tecla 'b'.\n");
    printf(" Para finalizar el programa presione la tecla 'q'.\n");
}


void map_portA (ALLEGRO_BITMAP *led_high, ALLEGRO_BITMAP *led_low)           
{                                       
	if(p.puertAB.PortA.bits.b7==1)            
	{
		al_draw_bitmap(led_high,378,56,0);       //se carga una imagen de un led encendido
	}
        else
        {
                al_draw_bitmap(led_low,378,56,0);      //se carga una imagen de un led apagado
        }    
	if(p.puertAB.PortA.bits.b6==1)
	{
		al_draw_bitmap(led_high,473,56,0);
	}
        else
        {
                al_draw_bitmap(led_low,473,56,0);
        }    
	if(p.puertAB.PortA.bits.b5==1)
	{
		al_draw_bitmap(led_high ,568,56,0);
	}
        else
        {
                al_draw_bitmap(led_low,568,56,0);
        }    
	if(p.puertAB.PortA.bits.b4==1)
	{
		al_draw_bitmap(led_high ,664,56,0);
	}
        else
        {
                al_draw_bitmap(led_low,664,56,0);
        }    
	if(p.puertAB.PortA.bits.b3==1)
	{
		al_draw_bitmap(led_high ,759,56,0);
	}
        else
        {
                al_draw_bitmap(led_low,759,56,0);
        }    
	if(p.puertAB.PortA.bits.b2==1)
	{
		al_draw_bitmap(led_high ,855,56,0);
	}   
        else
        {
                al_draw_bitmap(led_low,855,56,0);
        }    
	if(p.puertAB.PortA.bits.b1==1)
	{
            
		al_draw_bitmap(led_high ,950,56,0);
	}
        else
        {
                al_draw_bitmap(led_low,950,56,0);
        }    
	if(p.puertAB.PortA.bits.b0==1)
	{
		al_draw_bitmap(led_high ,1034,56,0);
	}
        else                                
        {
                al_draw_bitmap(led_low,1034,56,0);
        }    
        al_flip_display();
        //al_rest(2.0);
}