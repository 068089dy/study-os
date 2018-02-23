#include "debug.h"

static void print_stack_trace();
static elf_t kernel_elf;

void init_debug(){
    //从grub提供的信息中获取内核符号表和代码地址信息
    kernel_elf = elf_from_multiboot(glb_mboot_ptr);
}

void print_sur_status(){
    static int round = 0;
    uint16_t reg1,reg2,reg3,reg4;
    asm volatile(
        "mov %%cs, %0;"
        "mov %%ds, %1;"
        "mov %%es, %2;"
        "mov %%ss, %3;"
        :"=m"(reg1),"=m"(reg2),"=m"(reg3),"=m"(reg4));
    ++round;
}
void print_stack_trace(){
    uint32_t *ebp,*eip;
    asm volatile("mov %%ebp,%0":"=r"(ebp));
    while(ebp){
        eip = ebp + 1;
        printk("[0x%x] %s\n",*eip,elf_lookup_symbol(*eip,&kernel_elf));
        ebp = (uint32_t*)*ebp;
    }
}

void panic(const char *msg){
    print_stack_trace();
    while(1);
}