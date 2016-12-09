/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "idt.h"
#include "isr.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};


/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/


#define IDT_INTR(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x98;                                                                  \
    idt[numero].attr = (unsigned short) 0x8E00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);

#define IDT_TRAP(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x98;                                                                  \
    idt[numero].attr = (unsigned short) 0x8F00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);

#define IDT_SYSTEM_CALL(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x98;                                                                  \
    idt[numero].attr = (unsigned short) 0xEE00;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);


void idt_inicializar() {
    IDT_INTR(0);
    IDT_INTR(1);
    IDT_INTR(2);
    IDT_TRAP(3);
    IDT_TRAP(4);
    IDT_INTR(5);
    IDT_INTR(6);
    IDT_INTR(7);
    IDT_INTR(8);
    IDT_INTR(9);
    IDT_INTR(10);
    IDT_INTR(11);
    IDT_INTR(12);
    IDT_INTR(13);
    IDT_INTR(14);
    IDT_INTR(15);
    IDT_INTR(16);
    IDT_INTR(17);
    IDT_INTR(18);
    IDT_INTR(19);

  //  IDT_ENTRY(32);
  //  IDT_ENTRY(33);
  //  IDT_ENTRY(0x50);
  //  IDT_ENTRY(0x66);
}
