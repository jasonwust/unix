.section .data
string1:
    .asciz "This is a test of the conversion program!\n"
length:
    .int 43
divisor:
    .int 4
.section .bbs
    .lcomm buffer,43
.section .text
.globl _start
_start:
    nop
    leal string1,%esi
    leal buffer,%edi
    movl length,%ecx
    shr $2,%ecx

    cld
    rep movsl
    movl length,%ecx
    addl $3,%ecx
    rep movsb
