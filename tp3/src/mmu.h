/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"

#define PDE_INDEX(virtual) (virtual >> 22) & 0x3FF//al hacer esto agarro exactamente 10 bits gracias al and y el shift 
#define PTE_INDEX(virtual) (virtual >> 12) & 0x3FF//al hacer esto agarro exactamente 10 bits gracias al and y el shift 

int proxima_pagina_libre_tierra();

int proxima_pagina_libre_mar();

void mmu_inicializar_dir_kernel();

unsigned int mmu_inicializar_dir_tarea(unsigned int number_task, unsigned int fisica);



void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char rw, unsigned char user);



void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3);



#endif	/* !__MMU_H__ */
