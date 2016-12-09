/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__


/* Definicion de la pantalla */
#define VIDEO_FILS 25
#define VIDEO_COLS 80
#define VIDEO_ADDR 0xB8000

#include "colors.h"
typedef struct casillero
{
	unsigned char caracter;
	unsigned char color;
} __attribute__((__packed__)) casillero;

void screen_pintar_pantalla();
void screen_limpiar_pantalla();
void screen_nombre(string s);
void screen_fondo_blanco();
void screen_modo_estado();


#endif  /* !__SCREEN_H__ */
