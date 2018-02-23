#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"
//描述符表元素
typedef struct gdt_entry_t{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;
//gdtr
typedef struct gdt_ptr_t{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

//初始化全局描述符表
void init_gdt();
//gdt/gdt.s汇编实现
extern void gdt_flush(uint32_t);

#endif