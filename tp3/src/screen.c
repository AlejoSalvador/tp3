/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"


void screen_pintar_pantalla()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	for (int i=0;i<VIDEO_FILS;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			struct casillero auxiliar = {.caracter = 205, .color= C_FG_BLACK+C_BG_BLACK};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		

		}
	}
	
	for (int j=0;j<VIDEO_COLS;j++)
	{
		struct casillero auxiliar = {.caracter = 205, .color= C_FG_WHITE+C_BG_BLACK};
		*(puntero+ 0*VIDEO_COLS+j)=auxiliar;	
	}

	for (int j=0;j<VIDEO_COLS;j++)
	{
		struct casillero auxiliar = {.caracter = 205, .color= C_FG_WHITE+C_BG_BLACK};
		*(puntero+ 24*VIDEO_COLS+j)=auxiliar;	
	}

}

void screen_limpiar_pantalla()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	for (int i=0;i<VIDEO_FILS;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			struct casillero auxiliar = {.caracter = 205, .color= C_FG_BLACK+C_BG_BLACK};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		

		}
	}


}

void screen_nombre(string nombre)
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	for (int i=0;i<VIDEO_FILS;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			if (i==1)&&()
			{
				struct casillero auxiliar = {.caracter = nombre[s], .color= C_FG_BLACK+C_BG_BLACK};
			
				*(puntero+ i*VIDEO_COLS+j)=auxiliar;		
			}
		}
	}


}

void screen_fondo_blanco()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	int i=0;
	for (int j=0;j<VIDEO_COLS;j++)
	{
		if (i==1)&&()
			{
				struct casillero auxiliar = {.caracter = nombre[s], .color= C_FG_BLACK+C_BG_BLACK};
			
				*(puntero+ i*VIDEO_COLS+j)=auxiliar;		
			}		
	}


}


void screen_modo_estado()
{
	screen_limpiar_pantalla();	
	screen_nombre('Chocolate Fenix Premium\La Veneciana')

	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	for (int i=0;i<1;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			struct casillero auxiliar = {.caracter = 205, .color= C_FG_BLACK+C_BG_BLACK};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		

		}
	}


}



void screen_modo_mapa()
{
	screen_pintar_mar();
	screen_pintar_tierra();
	screen_pintar_relojes();

}
void screen_pintar_tierra()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	struct casillero auxiliar = {.caracter = 205, .color= C_FG_GREEN+C_BG_GREEN};
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		
		}
	}
	for (int i=0;i<16;i++){
		
		*(puntero+ 3*VIDEO_COLS+i)=auxiliar;		
	}


}

void screen_pintar_mar()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	struct casillero auxiliar = {.caracter = 205, .color= C_FG_CYAN+C_BG_CYAN};
	for (int i=16;i<VIDEO_COLS;i++){
		
		*(puntero+ 3*VIDEO_COLS+i)=auxiliar;		
	}
	for (int i=4;i<VIDEO_FILS-1;i++)
	{
		for (int j=0;j<VIDEO_COLS;j++)
		{
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		
		}
	}

}
void screen_pintar_relojes()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	struct casillero auxiliar = {.caracter = 205, .color= C_FG_BLACK+C_BG_BLACK};
	for (int j=0;j<VIDEO_COLS;j++)
	{
		*(puntero+ 79*VIDEO_COLS+j)=auxiliar;		
	}
}
