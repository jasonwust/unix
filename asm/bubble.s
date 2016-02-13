#pabbing 冒泡排序汇编实现
.section .data
values:
    .int 105, 235, 61, 315, 134, 221, 53, 145, 117, 5 #整型数组
hello:
    .ascii "hello world\n"
    len= . -hello
.section .text
.globl _start
_start:
    movl $values, %esi
    movl $9, %ecx
    movl $9, %ebx
loop:
    movl (%esi),%eax
    cmp %eax, 4(%esi)
    jge skip
    xchg %eax, 4(%esi)      #将eax与esi+4交换
    movl %eax, (%esi)
skip:
    add $4, %esi     #esi 加4
    dec %ebx         #ebx自减1
    jnz loop
    dec %ecx
    jz end
movl $values, %esi
    movl %ecx,%ebx
    jmp loop
end:
    movl $hello,%ecx
    movl $len,%edx
    movl $1,%ebx
    movl $4,%eax
    int $0x80

    movl $1,%eax
    movl $0,%ebx
    int $0x80
