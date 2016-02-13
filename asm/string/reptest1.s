.section .data
value1:
    .ascii "This is a test string.\n"
.section .bbs
    .lcomm output,23
.section .text
.globl _start
_strat:
    nop
    leal value1,%esi
    leal output,%edi
    movl $23,%ecx
    cld
    rep movsb

    movl $1,%eax
    movl $0,%ebx
    int $0x80
