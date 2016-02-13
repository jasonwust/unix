.section .text
.globl _start
_start:
	movl $10,%eax
	movl $0,%ecx
	jmp loop
loop:
	addl %eax,%ecx
	dec %eax
	cmp $0,%eax
	jne loop
	movl $0,%ebx
	movl $1,%eax
	int $0x80
	