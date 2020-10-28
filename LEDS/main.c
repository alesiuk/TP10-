/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: valentino
 *
 * Created on 28 de octubre de 2020, 14:40
 */

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

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*DECLARAMOS RECURSOS NECESARIOS DE ALLEGRO*/
    
    ALLEGRO_DISPLAY *display;                       //se crean  puntero hacia estrucuras de allegro,
    ALLEGRO_BITMAP *imagen;                         
    ALLEGRO_BITMAP *bienvenida;                   //Bienvenida
    ALLEGRO_BITMAP *menu;                           //Instrucciones
    ALLEGRO_BITMAP *led;                            //LED prendido
    ALLEGRO_BITMAP *led_low;                        //LED apagado
    ALLEGRO_SAMPLE *music = NULL;                  //Musica
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;        //Cola de eventos
    
    /*INICIALIZAMOS ALLEGRO Y LOS RECURSOS NECESARIOS*/
    
    if (!al_init()){
        fprintf(stderr, "Unable to start allegro\n");       //realizo la inicializacion de allegro
        return -1;
    } else if (!al_init_image_addon()) {
        fprintf(stderr, "Unable to start image addon \n");  //si hubo un error en la inicializacion imprimo el srderr
        al_uninstall_system();
        return -1;
    } else if (!(display = al_create_display(LARGO, ANCHO))) {  //se controlan si hubi problemas en las
        fprintf(stderr, "Unable to create display\n");          //distintas inicializaciones 
        al_uninstall_system();
        al_shutdown_image_addon();                              
        return -1;
    } else if (!(imagen = al_load_bitmap("background.png"))) { // se carga en un bitmap la imagen que usaremis de base
        fprintf(stderr, "Unable to load background\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    } else if (!(bienvenida = al_load_bitmap("bienvenida.png"))) {    //se carga la imagen de bienvenida
        fprintf(stderr, "Unable to load bienvenida\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    } else if (!(menu = al_load_bitmap("menu.png"))) {    //se carga la imagen del menu
        fprintf(stderr, "Unable to load menu\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }else if (!(led = al_load_bitmap("led_high.png"))) {           //se carga imagen de led prendido
        fprintf(stderr, "Unable to load led\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(led_low = al_load_bitmap("led_low.png"))) {           //se carga imagen de led apagado
        fprintf(stderr, "Unable to load led_low\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    if (!al_install_audio()) {                                      //Inicializo el audio
        fprintf(stderr, "failed to initialize audio!\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }

    if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to reserve samples!\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }

    music = al_load_sample("kun.wap");

    if (!music) {
        printf("Audio clip sample not loaded!\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    
    
    
    /*INICIALIZO EVENTOS Y TECLADO*/
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(imagen);       //se libera la memoria dinamica 
        al_destroy_bitmap(led);
        al_destroy_bitmap(led_low);
        al_destroy_bitmap(bienvenida);
        al_destroy_bitmap(menu);
        al_uninstall_audio();
        al_destroy_sample(music);
        return -1;
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    al_register_event_source(event_queue, al_get_keyboard_event_source());       //Evento teclado
    al_register_event_source(event_queue, al_get_display_event_source(display)); //Cruz roja de salir
    
    
    
    /*BIENVENIDA POR BITMAP Y POR CONSOLA*/
    
    bienvenida();
    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);//Doy la bienvenida al usuario
    al_draw_scaled_bitmap(bienvenida,0, 0, al_get_bitmap_width(bienvenida), al_get_bitmap_height(bienvenida),0, 0, LARGO, ANCHO,0);
    al_flip_display();                                                  //Muestro la imagen de bienvenida
    BOOLEAN enter = FALSE;                                              //Ver si se presiono enter
    while (enter == FALSE){                                             //Me quedo aca hasta que se apriete enter o se cierre el programa
        ALLEGRO_EVENT ev0;            //Struct toma todos los eventos de la cola
        if (al_get_next_event(event_queue, &ev0)){                   //Damos entrada de teclado por allegro
            if (ev0.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display
                al_destroy_bitmap(imagen);       //se libera la memoria dinamica , destruyendo los elemntos usados
                al_destroy_bitmap(led);
                al_destroy_bitmap(led_low);
                al_destroy_bitmap(bienvenida);
                al_destroy_display(display);
                al_destroy_event_queue(event_queue);
                al_destroy_bitmap(menu);
                al_uninstall_audio();
                al_destroy_sample(music);
                return 0;
            }
            else if ((ev0.type == ALLEGRO_EVENT_KEY_DOWN) && (ev0.keyboard.keycode == ALLEGRO_KEY_ENTER)){
                enter = TRUE;
            }
        }
    }
    al_draw_scaled_bitmap(menu,0, 0, al_get_bitmap_width(menu), al_get_bitmap_height(menu),0, 0, LARGO, ANCHO,0);
    al_flip_display();                                                  //Muestro la imagen de bienvenida
    enter = FALSE;                                              //Ver si se presiono enter
    while (enter == FALSE){                                             //Me quedo aca hasta que se apriete enter o se cierre el programa
        ALLEGRO_EVENT ev1;            //Struct toma todos los eventos de la cola
        if (al_get_next_event(event_queue, &ev1)){                   //Damos entrada de teclado por allegro
            if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display
                al_destroy_bitmap(imagen);       //se libera la memoria dinamica , destruyendo los elemntos usados
                al_destroy_bitmap(led);
                al_destroy_bitmap(led_low);
                al_destroy_bitmap(bienvenida);
                al_destroy_display(display);
                al_destroy_event_queue(event_queue);
                al_destroy_bitmap(menu);
                al_uninstall_audio();
                al_destroy_sample(music);
                return 0;
            }
            else if ((ev1.type == ALLEGRO_EVENT_KEY_DOWN) && (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER)){
                enter = TRUE;
            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    
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

    return (EXIT_SUCCESS);
}

