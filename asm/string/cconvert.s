.section .data
string1:
    .asciz "This is a TEST, of the converstion program!\n"
length:
    .int 43
.section .text
.CODE32
.globl _start
_start:
    nop
    leal string1,%esi
    movl %esi,%edi
    movl length,%ecx
    cld
loop1:
    lodsb
    cmpb $'a',%al
    jl skip
    cmpb $'z',%al
    jg skip
    subb $0x20,%al
skip:
    stosb
    loop loop1
end:
    pushl $string1
    call printf
    addl $4,%esp
    pushl $0
    call exit
