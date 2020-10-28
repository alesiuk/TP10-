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
    
    ///////////////////////////////////////////////
    /*DECLARAMOS RECURSOS NECESARIOS DE ALLEGRO*///
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ALLEGRO_DISPLAY *display;                       //se crean  puntero hacia estrucuras de allegro,        //
    ALLEGRO_BITMAP *imagen;                                                                                 //
    ALLEGRO_BITMAP *bienvenida;                   //Bienvenida                                              //
    ALLEGRO_BITMAP *menu;                           //Instrucciones                                         //
    ALLEGRO_BITMAP *led_high;                            //LED prendido                                     //
    ALLEGRO_BITMAP *led_low;                        //LED apagado                                           //
    ALLEGRO_SAMPLE *music = NULL;                  //Musica                                                 //
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;        //Cola de eventos                                       //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /////////////////////////////////////////////////////
    /*INICIALIZAMOS ALLEGRO Y LOS RECURSOS NECESARIOS*///
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!al_init()){                                                                                                                        //
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
    }else if (!(led_high = al_load_bitmap("led_high.png"))) {           //se carga imagen de led prendido
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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////
    /*INICIALIZO EVENTOS Y TECLADO*///
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    event_queue = al_create_event_queue();                                                             //
    if (!event_queue) {                                                                                //
        fprintf(stderr, "failed to create event_queue!\n");                                            //
        al_destroy_bitmap(imagen);       //se libera la memoria dinamica                               //
        al_destroy_bitmap(led_high);                                                                   //
        al_destroy_bitmap(led_low);                                                                    //
        al_destroy_bitmap(bienvenida);                                                                 //
        al_destroy_bitmap(menu);                                                                       //
        al_uninstall_audio();                                                                          //
        al_destroy_sample(music);                                                                      //
        return -1;                                                                                     //
    }                                                                                                  //
    if (!al_install_keyboard()) {                                                                      //
        fprintf(stderr, "failed to initialize the keyboard!\n");                                       //
        return -1;                                                                                     //
    }                                                                                                  //
    al_register_event_source(event_queue, al_get_keyboard_event_source());       //Evento teclado      //
    al_register_event_source(event_queue, al_get_display_event_source(display)); //Cruz roja de salir  //
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    /////////////////////////////////////////
    /*BIENVENIDA POR BITMAP Y POR CONSOLA*///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bienvenida();                                                                                                                                                        //
    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);              //Damos bienvenida al usuario                                                        //
    al_draw_scaled_bitmap(bienvenida,0, 0, al_get_bitmap_width(bienvenida), al_get_bitmap_height(bienvenida),0, 0, LARGO, ANCHO,0);                                      //
    al_flip_display();                                                      //Muestro la imagen de bienvenida                                                            //
    int mientras = FALSE;                                                  //Ver si se presiono enter                                                                    //
    while (mientras == FALSE){                                             //Me quedo aca hasta que se apriete enter o se cierre el programa                             //
        ALLEGRO_EVENT ev0;                                                 //Struct toma todos los eventos de la cola                                                    //
        if (al_get_next_event(event_queue, &ev0)){                   //Damos entrada de teclado por allegro                                                              //
            if (ev0.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display                                                                     //
                al_destroy_bitmap(imagen);                           //se libera la memoria dinamica                                                                     //
                al_destroy_bitmap(led_high);                                                                                                                             //
                al_destroy_bitmap(led_low);                                                                                                                              //
                al_destroy_bitmap(bienvenida);                                                                                                                           //
                al_destroy_display(display);                                                                                                                             //
                al_destroy_event_queue(event_queue);                                                                                                                     //
                al_destroy_bitmap(menu);                                                                                                                                 //
                al_uninstall_audio();                                                                                                                                    //
                al_destroy_sample(music);                                                                                                                                //
                return 0;                                                                                                                                                //
            }                                                                                                                                                            //
            else if ((ev0.type == ALLEGRO_EVENT_KEY_DOWN) && (ev0.keyboard.keycode == ALLEGRO_KEY_ENTER)){              //sino tranqui, salgo del while sin problema     //
                mientras = TRUE;                                                                                                                                         //
            }                                                                                                                                                            //
        }                                                                                                                                                                //
    }                                                                                                                                                                    //
    al_draw_scaled_bitmap(menu,0, 0, al_get_bitmap_width(menu), al_get_bitmap_height(menu),0, 0, LARGO, ANCHO,0);                                                        //
    al_flip_display();                                                                                             //Muestro la imagen de bienvenida                     //
    mientras = FALSE;                                                                                             //Ver si se presiono enter                             //
    while (mientras == FALSE){                                                                                    //Me quedo aca hasta que se apriete enter o se cierre  //
        ALLEGRO_EVENT ev1;                                                                                       //Struct toma todos los eventos de la cola              //
        if (al_get_next_event(event_queue, &ev1)){                                                              //Damos entrada de teclado por allegro                   //
            if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE){                                                       //Si se quiso cerrar el display                          //
                al_destroy_bitmap(imagen);                                                                      //se libera la memoria dinamica                          //
                al_destroy_bitmap(led_high);                                                                                                                             //
                al_destroy_bitmap(led_low);                                                                                                                              //
                al_destroy_bitmap(bienvenida);                                                                                                                           //
                al_destroy_display(display);                                                                                                                             //
                al_destroy_event_queue(event_queue);                                                                                                                     //
                al_destroy_bitmap(menu);                                                                                                                                 //
                al_uninstall_audio();                                                                                                                                    //
                al_destroy_sample(music);                                                                                                                                //
                return 0;                                                                                                                                                //
            }                                                                                                                                                            //
            else if ((ev1.type == ALLEGRO_EVENT_KEY_DOWN) && (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER)){      //sino tranqui, salgo del while sin problema             //
                enter = TRUE;                                                                                                                                            //
            }                                                                                                                                                            //
        }                                                                                                                                                                //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    /////////////////////////////
    /*PROTOBOARD CON LOS LEDS*///
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    al_draw_scaled_bitmap(imagen,0, 0, al_get_bitmap_width(imagen), al_get_bitmap_height(imagen),0, 0, LARGO, ANCHO,0);               //imagen del protoboard                                   //
    al_flip_display();                                                                                                               //se muestra los led en estado inicial. Apagados           //
    al_rest(2.0);                                                                                                                   //delay                                                     //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    
    /*Ingresar datos (sigo con el main)*/
    
    int end = FALSE;                                                    //Variable para terminar el programa
    int got_input;                                                      //Iniciamos una variable para saber si tuvimos entrada
    while (end == FALSE){                                               //Mientras no se quiera finalizar el programa
        got_input = FALSE;                                              //No hubo entrada aun  
        while (got_input == FALSE){                                     //Y mientras no haya entrada hago que Allegro ingrese la entrada por teclado
            ALLEGRO_EVENT ev;                                           //Struct toma todos los eventos de la cola
            if (al_get_next_event(event_queue, &ev)){                   //Damos entrada de teclado por allegro
                if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display
                    end = TRUE;                                         //Se termina el programa salgo de los while
                    got_input = TRUE;                                   //Recibimos entrada
                }
                else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){            //Vemos si se presiono una tecla
                    if (ev.keyboard.keycode == ALLEGRO_KEY_Q){          //Si se presiono la Q salimos
                        printf ("Gracias! Vuelva a jugar cuando quiera.\n");
                        al_destroy_bitmap(imagen);                      //se libera la memoria dinamica 
                        al_destroy_bitmap(led_high);
                        al_destroy_bitmap(led_low);
                        al_destroy_bitmap(bienvenida);
                        al_destroy_display(display);
                        al_destroy_event_queue(event_queue);
                        al_destroy_bitmap(menu);
                        al_uninstall_audio();
                        al_destroy_sample(music);
                        return 0;                                           //Vuelvo al sistema operativo
                        printf("\n");
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_T){         //Si se apreto la 't'
                        sw('t');                                            //Como siempre se le pasan datos validos y verificados a las funciones,
                        map_portA(led_high, led_low);                       //Actualizo la imagen
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_C){         //Si se apreto la 'c'
                        sw('c');
                        map_portA(led_high, led_low); 
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_S){         //Si se apreto la 's'
                        sw('s');  
                        map_portA(led_high, led_low); 
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_B){         //Si se apreto la 'b'
                        printf("La funcion Blink terminara luego de algunos destellos.\n");
                        p.portD.W=Blink(led_high, led_low);
                        map_portA(led_high, led_low);
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_0){             //si se apreto el 0
                        sw('0');                                              //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                        //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_1){         //si se apreto el 1
                        sw('1');                                            //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                       //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_2){            //si se apreto el 2
                        sw('2');                                             //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                       //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_3){         //si se apreto el 3
                        sw('3');                                            //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                       //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_4){          //si se apreto el 4
                        sw('4');                                             //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                        //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_5){         //si se apreto el 5
                        sw('5');                                             //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                        //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_6){         //si se apreto el 6
                        sw('6');                                            //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                       //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_7){         //si se apreto el 7
                        sw('7');                                            //Seteo el numero de bit pedido
                        map_portA(led_high, led_low);                       //Cambio el estado de los LEDS (grafico)
                        got_input = TRUE;                                   //Recibimos entrada
                    }
                }
            }
        }
	printf("\n");
	if (end != TRUE){		//Si el usuario no decidio salir
            print_portA();		//Imprimo los cambios del puerto
        }
    }
    al_destroy_bitmap(imagen);       //se libera la memoria dinamica
    al_destroy_bitmap(led_high);
    al_destroy_bitmap(led_low);
    al_destroy_bitmap(bienvenida);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(menu);
    al_uninstall_audio();
    al_destroy_sample(music);
    
    return (EXIT_SUCCESS);

}
 
   

