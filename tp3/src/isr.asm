; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


;; PIC
extern fin_intr_pic1
;;IDT
extern int_teclado


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

msg%1_msg: DB 'Excepcion ', %1 / 10 + '0', %1 % 10 + '0'
msg%1_len: equ $ - msg%1_msg

_isr%1:
.loopear:
    ; To Infinity And Beyond!!
xchg bx, bx
    mov eax, 0xFFF2
    mov ebx, 0xFFF2
    mov ecx, 0xFFF2
    mov edx, 0xFFF2
    imprimir_texto_mp msg%1_msg, msg%1_len, 0x07, 1, 0
    
    jmp $
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
reloj_numero:           dd 0x00000000
reloj:                  db '|/-\'


;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

global _isr32

_isr32:
	
	pushad
	call proximo_reloj
	call fin_intr_pic1
	popad
iret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
make
global _isr33
_isr33:

	pushad
	
	xor eax, eax
	in al, 0x60
	push eax
	call int_teclado

	pop eax
	call fin_intr_pic1
	popad
iret

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

global _isr0x50
_isr0x50:
	pushad
	mov eax, 0x42

	popad
iret

global _isr0x66
_isr0x66:
	pushad

	mov eax, 0x42	

	popad
iret

;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
    pushad
    inc DWORD [reloj_numero]
    mov ebx, [reloj_numero]
    cmp ebx, 0x4
    jl .ok
        mov DWORD [reloj_numero], 0x0
        mov ebx, 0
    .ok:
        add ebx, reloj
        imprimir_texto_mp ebx, 1, 0x0f, 24, 79

    popad
    ret
