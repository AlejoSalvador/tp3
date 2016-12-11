/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "defines.h"
#include "mmu.h"
#include "gdt.h"
#include "i386.h"

#define GDT_NAVIOS(numero, indice)	\
  gdt[numero].base_0_15  = (unsigned short) ((unsigned int) &(tss_navios[indice])); \
  gdt[numero].base_23_16 = (unsigned char)  ((unsigned int) (&(tss_navios[indice]))>>16); \
  gdt[numero].base_31_24 = (unsigned char)  ((unsigned int) (&(tss_navios[indice]))>>24);	

#define GDT_BANDERAS(numero, indice)	\
  gdt[numero].base_0_15  = (unsigned short) ((unsigned int) &(tss_banderas[indice])); \
  gdt[numero].base_23_16 = (unsigned char)  ((unsigned int) (&(tss_banderas[indice]))>>16); \
  gdt[numero].base_31_24 = (unsigned char) ((unsigned int) (&(tss_banderas[indice]))>>24); 

tss tarea_inicial;
tss tarea_idle;

tss tss_navios[CANT_TAREAS];
tss tss_banderas[CANT_TAREAS];

void tss_inicializar() 
{

	gdt[GDT_TAREA_INICIAL].base_0_15  = (unsigned short) ((unsigned int) &(tarea_inicial));
	gdt[GDT_TAREA_INICIAL].base_23_16 = (unsigned char)  ((unsigned int) (&(tarea_inicial))>>16);
	gdt[GDT_TAREA_INICIAL].base_31_24 = (unsigned char)  ((unsigned int) (&(tarea_inicial))>>24); 

	gdt[GDT_TAREA_IDLE].base_0_15  = (unsigned short) ((unsigned int) &(tarea_idle));
	gdt[GDT_TAREA_IDLE].base_23_16 = (unsigned char)  ((unsigned int) (&(tarea_idle))>>16);
	gdt[GDT_TAREA_IDLE].base_31_24 = (unsigned char)  ((unsigned int) (&(tarea_idle))>>24); 

	GDT_NAVIOS(GDT_TAREA_1, 0)
	GDT_NAVIOS(GDT_TAREA_2, 1)
	GDT_NAVIOS(GDT_TAREA_3, 2)
	GDT_NAVIOS(GDT_TAREA_4, 3)
	GDT_NAVIOS(GDT_TAREA_5, 4)
	GDT_NAVIOS(GDT_TAREA_6, 5)
	GDT_NAVIOS(GDT_TAREA_7, 6)
	GDT_NAVIOS(GDT_TAREA_8, 7)

	GDT_BANDERAS(GDT_TAREA_1_BANDERA, 0)
	GDT_BANDERAS(GDT_TAREA_2_BANDERA, 1)
	GDT_BANDERAS(GDT_TAREA_3_BANDERA, 2)
	GDT_BANDERAS(GDT_TAREA_4_BANDERA, 3)
	GDT_BANDERAS(GDT_TAREA_5_BANDERA, 4)
	GDT_BANDERAS(GDT_TAREA_6_BANDERA, 5)
	GDT_BANDERAS(GDT_TAREA_7_BANDERA, 6)
	GDT_BANDERAS(GDT_TAREA_8_BANDERA, 7)

	tarea_inicial= (tss){
	    (unsigned short)  0,//ptl;
	    (unsigned short)  0,//unused0;
	    (unsigned int)    0,//esp0;
	    (unsigned short)  0,//ss0;
	    (unsigned short)  0,//unused1;
	    (unsigned int)    0,//esp1;
	    (unsigned short)  0,//ss1;
	    (unsigned short)  0,//unused2;
	    (unsigned int)    0,//esp2;
	    (unsigned short)  0,//ss2;
	    (unsigned short)  0,//unused3;
	    (unsigned int)    0,//cr3;
	    (unsigned int)    0,//eip;
	    (unsigned int)    0,//eflags;
	    (unsigned int)    0,//eax;
	    (unsigned int)    0,//ecx;
	    (unsigned int)    0,//edx;
	    (unsigned int)    0,//ebx;
	    (unsigned int)    0,//esp;
	    (unsigned int)    0,//ebp;
	    (unsigned int)    0,//esi;
	    (unsigned int)    0,//edi;
	    (unsigned short)  0,//es;
	    (unsigned short)  0,//unused4;
	    (unsigned short)  0,//cs;
	    (unsigned short)  0,//unused5;
	    (unsigned short)  0,//ss;
	    (unsigned short)  0,//unused6;
	    (unsigned short)  0,//ds;
	    (unsigned short)  0,//unused7;
	    (unsigned short)  0,//fs;
	    (unsigned short)  0,//unused8;
	    (unsigned short)  0,//gs;
	    (unsigned short)  0,//unused9;
	    (unsigned short)  0,//ldt;
	    (unsigned short)  0,//unused10;
	    (unsigned short)  0,//dtrap;
	    (unsigned short)  0,//iomap;
	};

	tarea_idle= (tss){
	    (unsigned short)  0,//ptl;
	    (unsigned short)  0,//unused0;
	    (unsigned int)    0x0002A000,//esp0;
	    (unsigned short)  0XA8,//ss0;
	    (unsigned short)  0,//unused1;
	    (unsigned int)    0,//esp1;
	    (unsigned short)  0,//ss1;
	    (unsigned short)  0,//unused2;
	    (unsigned int)    0,//esp2;
	    (unsigned short)  0,//ss2;
	    (unsigned short)  0,//unused3;
	    (unsigned int)    0x27000,//cr3;
	    (unsigned int)    0x40000000,//eip 0x400000000;
	    (unsigned int)    0x202,//eflags;
	    (unsigned int)    0,//eax;
	    (unsigned int)    0,//ecx;
	    (unsigned int)    0,//edx;
	    (unsigned int)    0,//ebx;
	    (unsigned int)    0x0002A000,//esp;
	    (unsigned int)    0x0002A000,//ebp;
	    (unsigned int)    0,//esi;
	    (unsigned int)    0,//edi;
	    (unsigned short)  0xA8,//es;
	    (unsigned short)  0,//unused4;
	    (unsigned short)  0x98,//cs;
	    (unsigned short)  0,//unused5;
	    (unsigned short)  0xA8,//ss;
	    (unsigned short)  0,//unused6;
	    (unsigned short)  0xA8,//ds;
	    (unsigned short)  0,//unused7;
	    (unsigned short)  0xA8,//fs;
	    (unsigned short)  0,//unused8;
	    (unsigned short)  0xA8,//gs;
	    (unsigned short)  0,//unused9;
	    (unsigned short)  0,//ldt;
	    (unsigned short)  0,//unused10;
	    (unsigned short)  0,//dtrap;
	    (unsigned short)  0xFFFF,//iomap;
	};

	

	int mar = 0x100000;
	int i;
	for (i = 0; i < CANT_TAREAS; i++)
	{

		unsigned int* next_page=(unsigned int*) proxima_pagina_libre_tierra();
		tss_navios[i]= (tss){
		    (unsigned short)  0,//ptl;
		    (unsigned short)  0,//unused0;
		    (unsigned int)    next_page+0x800,//esp0;
		    (unsigned short)  0XA8,//ss0;
		    (unsigned short)  0,//unused1;
		    (unsigned int)    0,//esp1;
		    (unsigned short)  0,//ss1;
		    (unsigned short)  0,//unused2;
		    (unsigned int)    0,//esp2;
		    (unsigned short)  0,//ss2;
		    (unsigned short)  0,//unused3;
		    (unsigned int)    mmu_inicializar_dir_tarea(i+1, mar),//cr3;
		    (unsigned int)    0x40000000,//eip;
		    (unsigned int)    0x202,//eflags;
		    (unsigned int)    0,//eax;
		    (unsigned int)    0,//ecx;
		    (unsigned int)    0,//edx;
		    (unsigned int)    0,//ebx;
		    (unsigned int)    0x40001C00,//esp;
		    (unsigned int)    0x40001C00,//ebp;
		    (unsigned int)    0,//esi;
		    (unsigned int)    0,//edi;
		    (unsigned short)  0xA3,//es;
		    (unsigned short)  0,//unused4;
		    (unsigned short)  0x93,//cs;
		    (unsigned short)  0,//unused5;
		    (unsigned short)  0xA3,//ss;
		    (unsigned short)  0,//unused6;
		    (unsigned short)  0xA3,//ds;
		    (unsigned short)  0,//unused7;
		    (unsigned short)  0xA3,//fs;
		    (unsigned short)  0,//unused8;
		    (unsigned short)  0xA3,//gs;
		    (unsigned short)  0,//unused9;
		    (unsigned short)  0,//ldt;
		    (unsigned short)  0,//unused10;
		    (unsigned short)  0,//dtrap;
		    (unsigned short)  0xFFFF,//iomap;
		};
		mar+= 0x2000;

	tss_banderas[i]= (tss){
		    (unsigned short)  0,//ptl;
		    (unsigned short)  0,//unused0;
		    (unsigned int)    next_page+0x1000,//esp0;
		    (unsigned short)  0xA8,//ss0;
		    (unsigned short)  0,//unused1;
		    (unsigned int)    0,//esp1;
		    (unsigned short)  0,//ss1;
		    (unsigned short)  0,//unused2;
		    (unsigned int)    0,//esp2;
		    (unsigned short)  0,//ss2;
		    (unsigned short)  0,//unused3;
		    (unsigned int)    tss_navios[i].cr3,//cr3;
		    (unsigned int)    0x40000000+*((unsigned int*)(0x00001FFC+0x10000+0x2000*i)),//eip REVISARLO ESTA MAL;
		    (unsigned int)    0x202,//eflags;
		    (unsigned int)    0,//eax;
		    (unsigned int)    0,//ecx;
		    (unsigned int)    0,//edx;
		    (unsigned int)    0,//ebx;
		    (unsigned int)    0x40001FFC,//esp;
		    (unsigned int)    0x40001FFC,//ebp;
		    (unsigned int)    0,//esi;
		    (unsigned int)    0,//edi;
		    (unsigned short)  0xA8,//es;
		    (unsigned short)  0,//unused4;
		    (unsigned short)  0x98,//cs;
		    (unsigned short)  0,//unused5;
		    (unsigned short)  0xA8,//ss;
		    (unsigned short)  0,//unused6;
		    (unsigned short)  0xA8,//ds;
		    (unsigned short)  0,//unused7;
		    (unsigned short)  0xA8,//fs;
		    (unsigned short)  0,//unused8;
		    (unsigned short)  0xA8,//gs;
		    (unsigned short)  0,//unused9;
		    (unsigned short)  0,//ldt;
		    (unsigned short)  0,//unused10;
		    (unsigned short)  0,//dtrap;
		    (unsigned short)  0xFFFF,//iomap;
		};

	}




}

