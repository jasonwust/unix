#反转输出字符串
.section .data
string:
    .ascii "BASED ADDRESSING"
len= . - string
.section .bbs
    .lcomm buffer,100

.section .text
.global _start
_start:
    movl $string,%edi
    movl $len,%eax
    movl $buffer,%ebx
    jmp  loop
loop:
    dec %eax
    movb (%edi,%eax,1),%cl
    movb %cl,(%ebx)
    inc %ebx
    sub $0,%eax
    jnz loop;
    movl $4,%eax
    movl $1,%ebx
    movl $buffer,%ecx
    movl $len,%edx
    int $0x80

