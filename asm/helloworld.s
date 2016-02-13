#实现从键盘输入hello world 并输出
#如果不清楚系统调用函数参数可以使用man 2 function_name 查看
#如 man 2 read
#参数与寄存器对应关系为从左到右分别为ebx,ecx,edx,esi,edi
#超过5个参数将参数存入内存，ebx指定其首地址
#eax 用于指定系统调用的函数代码
#函数对应的宏代码定义可以在头文件/usr/include/asm/unistd.h中看到
.section .bbs                  #定义bbs段
    .lcomm buffer,30
.section .text
.globl _start
_start:
    movl $buffer,%ecx       #下面三条语句将sys_read参数分别传入到相应寄存器，$加变量名相当于取地址
    movl $30,%edx
    movl $0,%ebx
    movl $3,%eax            #系统调用sys_read函数代码
    int $0x80               #使用ox80指定执行系统调用中断代码

    movl $1,%ebx
    movl $4,%eax            #系统调用sys_write
    int $0x80

    movl $0,%ebx
    movl $1,%eax            #系统调用sys_exit
    int $0x80
