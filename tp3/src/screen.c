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
			struct casillero auxiliar = {.caracter = 205, .color= C_FG_LIGHT_GREY+C_BG_LIGHT_GREY};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		

		}
	}


}

void screen_navio_naming()
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	for (int i=2;i<10;i=i+7)
	{
		for (int j=5;j<50;j=j+12)
		{
				struct casillero auxiliar = {.caracter = 'N', .color= C_FG_BLACK+C_BG_LIGHT_GREY};
				*(puntero+ i*VIDEO_COLS+j)=auxiliar;

				auxiliar.caracter = 'A';
				*(puntero+ i*VIDEO_COLS+j+1)=auxiliar;	

				auxiliar.caracter = 'V';
				*(puntero+ i*VIDEO_COLS+j+2)=auxiliar;

				auxiliar.caracter = 'I';
				*(puntero+ i*VIDEO_COLS+j+3)=auxiliar;

				auxiliar.caracter = 'O';
				*(puntero+ i*VIDEO_COLS+j+4)=auxiliar;	

				auxiliar.color = C_FG_LIGHT_GREY+C_BG_LIGHT_GREY;
				*(puntero+ i*VIDEO_COLS+j+5)=auxiliar;
				auxiliar.color = C_FG_BLACK+C_BG_LIGHT_GREY;
				auxiliar.caracter = '0'+1+ j/12 + 4*(i/7);
				*(puntero+ i*VIDEO_COLS+j+6)=auxiliar;

		
		}
	}


}

void screen_nombre(char nombre[])
{
	struct casillero *puntero= (casillero *)VIDEO_ADDR; 
	int i=0;
	for (int j=0;j<VIDEO_COLS;j++)
	{
		if (j<36)
		{
			struct casillero auxiliar ={.caracter = nombre[j], .color= C_FG_WHITE+C_BG_BLACK};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;		
		} else
		{
			struct casillero auxiliar ={.caracter = 205, .color= C_FG_BLACK+C_BG_BLACK};
			
			*(puntero+ i*VIDEO_COLS+j)=auxiliar;

		}		
	}


}


void screen_modo_estado()
{
	screen_limpiar_pantalla();
	char nombre[] = "Chocolate Fenix Premium/La Veneciana";	
	screen_nombre(nombre);
	screen_navio_naming();


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
