.section .bbs
    .lcomm x,4
    .lcomm y,4
    .lcomm buffer,4
.section .text
.globl _start
_start:
    movl $3,%eax
    movl $0,%ebx
    movl $buffer,%ecx
    movl $4,%edx
    int $0x80

    movl (buffer),%eax
    movl %eax,(x)

    movl $3,%eax
    movl $0,%ebx
    movl $buffer,%ecx
    movl $4,%edx
    int $0x80

    movl (buffer),%eax
    movl %eax,(y)

    add (x),%eax

    movl %eax,(buffer)


    movl $4,%eax
    movl $1,%ebx
    movl $buffer,%ecx
    movl $4,%edx
    int $0x80

