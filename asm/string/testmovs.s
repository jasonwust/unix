.section .data
value1:
    .ascii "this is a test string.\n"
.section .bbs
    .lcomm output,23
.section .text
.global _start
_start:
    nop
    leal value1,%esi
    leal output,%edi
    movsb
    movsw
    movsl

    mov $1,%eax
    mov $0,%ebx
    int $0x80
