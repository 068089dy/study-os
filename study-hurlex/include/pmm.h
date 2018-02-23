#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H
#include "multiboot.h"
//线程栈大小
#define STACK_ZIZE 8192
//支持的最大物理内存(512MB)
#define PMM_MAX_SIZE 0x20000000
//物理页大小（4k）
#define PMM_PAGE_SIZE 0x1000
//最多有几页物理页
#define PAGE_MAX_SIZE (PMM_MAX_SIZE/PMM_PAGE_SIZE)
//
#define PHY_PAGE_MASK 0cffff000
//
extern uint32_t phy_page_count;
//内核起始位置
extern uint8_t kern_start[];
//内核结束位置
extern uint8_t kern_end[];


/*
函数
*/
void show_mm();
void init_pmm();
uint32_t pmm_alloc_page();
void pmm_free_page(uint32_t p);
#endif