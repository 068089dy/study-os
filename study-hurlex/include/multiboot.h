#ifndef INCLUDE_MUILTBOOT_H_
#define INCLUDE_MUILTBOOT_H_

#include "types.h"
//__attribute__ ((packed)) 的作用就是告诉编译器取消结构在编译过程中的优化对齐,
//按照实际占用字节数进行对齐，是GCC特有的语法。
//这个功能是跟操作系统没关系，跟编译器有关，gcc编译器不是紧凑模式的，
typedef struct multiboot_t{
    uint32_t flags;//multiboot版本信息
    /**
    * 从 BIOS 获知的可用内存
    *
    * mem_lower 和 mem_upper 分别指出了低端和高端内存的大小,单位是。K
    * 低端内存的首地址是 0 ,高端内存的首地址是 1M 。
    * 低端内存的最大可能值是 640K
    * 高端内存的最大可能值是最大值减去 1M 。但并不保证是这个值。
    */
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;

    //elf格式内核映像的setion头
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;

    //由bios提供的内存分布的缓冲区
    //缓冲区由一个或多个下面的mmap_entry_t组成
    uint32_t mmap_length;//缓冲区总大小
    uint32_t mmap_addr;//缓冲区地址

    uint32_t drivers_length;//第一个驱动器结构的物理地址
    uint32_t drivers_addr;//第一个驱动器结构的大小
    uint32_t config_table;//rom配置表
    uint32_t boot_loader_name;//bootloader名字
    uint32_t apm_table;//apm
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;

} __attribute__((packed)) multiboot_t;


//声明全局multiboot_t指针
extern multiboot_t *glb_mboot_ptr;
#endif