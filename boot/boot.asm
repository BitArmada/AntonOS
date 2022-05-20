
[ org 0x7c00 ]

KERNEL_OFFSET equ 0x1000


; Set the stack.
mov bp , 0x9000
mov sp , bp

call load_kernel
call switch_to_pm

jmp $


; includes
%include "print.asm"
%include "disk.asm"
%include "./gdt.asm"
%include "./switch_to_pm.asm"




[ bits 16]

; load_kernel
load_kernel:
    mov bx , KERNEL_OFFSET ; Set -up parameters for our disk_load routine , so
    mov dh , 15 ; that we load the first 15 sectors ( excluding
    mov dl , [BOOT_DRIVE] ; the boot sector ) from the boot disk ( i.e. our
    call disk_load ; kernel code ) to address KERNEL_OFFSET
    ret




[bits 32]

BEGIN_PM: ; This is where we arrive after switching to and initialising protected mode.
    mov ebx , MSG_PROT_MODE
    call print_string_pm ; Use our 32 - bit print routine.

    call KERNEL_OFFSET

    jmp $ ; Hang.



; Global variables
BOOT_DRIVE db 0
MSG_PROT_MODE db " Successfully landed in 32 - bit Protected Mode " , 0


times 510 -( $ - $$ ) db 0 ; When compiled , our program must fit into 512 bytes ,

dw 0xaa55 ; Last two bytes ( one word ) form the magic number ,