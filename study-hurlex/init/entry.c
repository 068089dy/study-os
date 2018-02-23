#include "types.h"
#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "pmm.h"
int kern_entry()
{	
	//初始化调试
	init_debug();
	//初始化gdt
	init_gdt();
	//初始化idt
	init_idt();
	//
	init_pmm();
	//清屏
	console_clear();

	printk("hello!\n");
	//中断测试
	asm volatile("int $0x3");
	asm volatile("int $0x4");
	//显示物理内存块
	show_mm();
	//物理内存分配测试
	uint32_t allc_addr = NULL;
	printk("Test Physical Memory Alloc:\n");
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: %d MB %d kb %d b\n",(allc_addr - allc_addr%1024)/(1024*1024) , allc_addr%(1024*1024)/1024 , allc_addr%1024);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: %d MB %d kb %d b\n",(allc_addr - allc_addr%1024)/(1024*1024) , allc_addr%(1024*1024)/1024 , allc_addr%1024);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: %d MB %d kb %d b\n",(allc_addr - allc_addr%1024)/(1024*1024) , allc_addr%(1024*1024)/1024 , allc_addr%1024);
	pmm_free_page(allc_addr);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: %d MB %d kb %d b\n",(allc_addr - allc_addr%1024)/(1024*1024) , allc_addr%(1024*1024)/1024 , allc_addr%1024);

	
    return 0;
}
