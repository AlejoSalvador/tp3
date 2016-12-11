; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start


;; GDT
extern GDT_DESC

;; IDT
extern IDT_DESC
extern idt_inicializar

extern tss_inicializar

;;salida
extern screen_pintar_pantalla
extern screen_modo_estado
extern screen_modo_mapa
;; PIC
extern resetear_pic
extern habilitar_pic

;;PAGINACION
extern mmu_inicializar_kernel
extern mmu_inicializar_dir_tarea
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; habilitar A20
    call habilitar_A20
    ; cargar la GDT
    LGDT [GDT_DESC]
    ; setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1
    mov cr0, eax
	
    ; pasar a modo protegido
    jmp 0X98:mp

    ; acomodar los segmentos
BITS 32
mp:
    xor eax, eax
    mov ax, 0xA8
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov ss, ax
    mov ax, 0xB0
    mov fs, ax    

    ; setear la pila
    mov esp, 0x27000
    mov ebp, 0x27000
    ; pintar pantalla, todos los colores, que bonito!
    call screen_modo_estado

    call screen_modo_mapa

    ; inicializar el manejador de memoria
    call mmu_inicializar_kernel

    ; inicializar el directorio de paginas
    mov eax, 0x27000
    mov cr3, eax
    ; inicializar memoria de tareas


    ; habilitar paginacion
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; inicializar tarea idle

    ; inicializar todas las tsss

    ; inicializar entradas de la gdt de las tsss
    call tss_inicializar


    ; inicializar el scheduler

    ; inicializar la IDT
    lidt[IDT_DESC]
    call idt_inicializar


call screen_modo_mapa


	
    ; configurar controlador de interrupciones
	
	call resetear_pic
	call habilitar_pic
	sti

    ; cargar la tarea inicial
	
	mov ax, 0xB8
	ltr ax	

    ; saltar a la primer tarea recordar que debo corregir el EIP de las banderas
	xchg bx, bx	
	jmp 0xC0:0	

    ; Ciclar infinitamente (por si algo sale mal...)
	
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
