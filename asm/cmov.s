#cmovtest.s
.section .data
output:
    .ascii "the lagest value is %d\n"
values:
    .int 105,235,61,315,134,221,53,145,117,5
.section .text
.globl main
main:
    nop
    movl values,%ebx
    movl $1,%edi
loop:
    movl values(,%edi,4),%eax    #values+edi*4
    cmp %ebx,%eax
    cmova %eax,%ebx
    inc %edi
    jne loop
    pushl %ebx
    pushl $outut
    call printf
    addl $8,%esp
    pushl $0
    call  exit
