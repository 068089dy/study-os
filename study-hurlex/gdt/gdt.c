#include "gdt.h"
#include "string.h"
//gdt元素个数
#define GDT_LENGTH 5
//gdt
gdt_entry_t gdt_entries[GDT_LENGTH];
//gdtr
gdt_ptr_t gdt_ptr;
/*
数组下标，基址，长度，访问标志，其他访问标志；
*/
static void gdt_set_gate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran);
//内核栈地址
extern uint32_t stack;

//
void init_gdt(){
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
    gdt_ptr.base = (uint32_t) & gdt_entries;

    gdt_set_gate(0,0,0,0,0);
    gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF);
    gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);
    gdt_set_gate(3,0,0xFFFFFFFF,0xFA,0xCF);
    gdt_set_gate(4,0,0xFFFFFFFF,0xF2,0xCF);

    gdt_flush((uint32_t)&gdt_ptr);
}
// uint16_t limit_low;
//     uint16_t base_low;
//     uint8_t base_middle;
//     uint8_t access;
//     uint8_t granularity;
//     uint8_t base_high;
static void gdt_set_gate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran){
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = (access & 0xFF);
}

