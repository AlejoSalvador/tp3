/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

int pagina_libre_tierra = 0x30000;

int proxima_pagina_libre_tierra()
{
	pagina_libre_tierra += 0x1000;
	return pagina_libre_tierra;
}

int pagina_libre_mar = 0x100000;

int proxima_pagina_libre_mar()
{
	pagina_libre_mar += 0x1000;
	return pagina_libre_mar;
}



void mmu_inicializar_kernel()
{
	unsigned int* page_directory = (unsigned  int*) 0x27000; 
	page_directory[0]=0x00028003;
	page_directory[1]=0x00030003;

	for (int i=2; i < 1024;i++){
		page_directory[i]=0x00000000;
	}

	unsigned int* page_table_0 = (unsigned  int*) 0x28000;
	for (int i=0; i < 1024;i++)
	{
		page_table_0[i]=(i<<12)+3;
	}

	unsigned int* page_table_1 = (unsigned int*) 0x30000;
	for (int i=0; i < 896;i++)
	{
		page_table_1[i]=(i<<12)+0x400000+3;
	}

	for (int i=896; i < 1024;i++)
	{
		page_table_1[i]=0x00000002;
	}
	mmu_mapear_pagina(0x40000000,0x27000,0x20000, 0, 0);
	tlbflush();

}


void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char rw, unsigned char user)
{

	unsigned int* dir_entry = (unsigned int*) cr3;
	unsigned int pd_index = PDE_INDEX(virtual);
	unsigned int pt_index = PTE_INDEX(virtual);

	unsigned int* pd= &(dir_entry[pd_index]);
	unsigned int* pt;

	if(((*pd)&1) == 1)
	{
		// PDE_ENTRY esta presente
		pt = (unsigned int*) (((*pd)>>12)<<12);

	} else
	{
		// Tengo que crear la entrada y las tablas ??? REVISAR LO DE ABAJO
		
		*pd=proxima_pagina_libre_tierra()+0X00000001+user*4+rw*2;
		pt=(unsigned int*) pagina_libre_tierra;
		
		int i;
		for (i = 0; i < 1024 ; i++)
		{
			pt[i] = 0x00000000;
		}
	}
	pt[pt_index]=fisica+user*4+rw*2+1;
		
	tlbflush();
}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3)
{
	unsigned int* dir_entry = (unsigned int*) cr3;
	unsigned int pd_index = PDE_INDEX(virtual);
	unsigned int pt_index = PTE_INDEX(virtual);

	
	unsigned int* pd= &(dir_entry[pd_index]);
	unsigned int* pt= (unsigned int*) (((*pd)>>12)<<12); 
	pt[pt_index]=0x00000000;
	tlbflush();
}

unsigned int mmu_inicializar_dir_tarea(unsigned int number_task, unsigned int fisica)
{
	unsigned int dir_directory = proxima_pagina_libre_tierra();
	unsigned int* dir_entry = (unsigned int*) dir_directory;
	unsigned int dir_table = proxima_pagina_libre_tierra();
	unsigned int* tab_entry = (unsigned int*) dir_table;

	dir_entry[0]=dir_table+3;
	
	for (int i=0;i<1024;i++)
	{
		tab_entry[i]=(i<<12)+3;
	}
	
	unsigned int dir_table2 = proxima_pagina_libre_tierra();
	unsigned int* tab_entry2 = (unsigned int*) dir_table2;

	dir_entry[1]=dir_table2+3;

	for (int i=0;i<896;i++)
	{
		tab_entry2[i]=((i+1024)<<12)+3;
	}

	for (int i=896;i<1024;i++)
	{
		tab_entry2[i]=0;
	}

	for (int i=2;i<1024;i++)
	{
		dir_entry[i]=0;
	}

	mmu_mapear_pagina(0x40000000,dir_directory, fisica, 1, 1);
	mmu_mapear_pagina(0x40001000,dir_directory, fisica+0x1000, 1, 1);
	mmu_mapear_pagina(0x40002000,dir_directory, 0, 0, 1);//ancla

	//mmu_mapear_pagina(fisica, rcr3(), fisica, 1, 1);
	//mmu_mapear_pagina(fisica+0x1000, rcr3(), fisica+0x1000, 1, 1);

	unsigned int* src=(unsigned int*) 0x8000+(0x2000)*number_task;
	unsigned int* dst=(unsigned int*) fisica;
	for (int i=0;i<2048;i++)
	{
		*(dst) = *(src);	
		dst++;
		src++;
	}

	//mmu_unmapear_pagina(fisica, rcr3());
	//mmu_unmapear_pagina(fisica+0x1000, rcr3());	

	tlbflush();
	return dir_directory;//devolver cr3

}

