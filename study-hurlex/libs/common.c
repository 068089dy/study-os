#include "common.h"
//函数前面加上inline之后,编译器会尝试在该函数的调用点直接进行代码展开,而不是传统的函数调用
//端口写一个字节
inline void outb(uint16_t port,uint8_t value){
    /*
    c内联汇编：
    */
    asm volatile("outb %1,%0"::"dN" (port),"a"(value));
}
//端口读一个字节
inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile("inb %1,%0":"=a"(ret):"dN"(port));
    return ret;
}
//端口读一个字
inline uint16_t inw(uint16_t port){
    uint16_t ret;
    asm volatile("inw %1,%0":"=a"(ret):"dN"(port));
    return ret;
}