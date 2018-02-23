#include "multiboot.h"
#include "common.h"
//#include "debug.h"
#include "pmm.h"
#define assert(x, info)                                       	\
	do {                                                	\
		if (!(x)) {                                     \
			panic(info); 		     		\
		}                                               \
	} while (0)

#define static_assert(x)    \
        switch(x){  \
            case 0:case(x): ;   \
        } 
// PMM_MAX_SIZE
// PMM_PAGE_SIZE
typedef struct mmap_entry_t {
    uint32_t size;
    uint32_t base_addr_low;
    uint32_t base_addr_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
} __attribute__((packed)) mmap_entry_t;

static uint32_t pmm_stack[PAGE_MAX_SIZE+1];
static uint32_t pmm_stack_top;
uint32_t phy_page_count;

void show_mm(){
    uint32_t mmap_length = glb_mboot_ptr->mmap_length;
    uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
    printk("mm_addr:0x%x\n",mmap_addr);
    printk("mm_length:0x%x\n",mmap_length);
    for(mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;mmap<mmap_addr+mmap_length;mmap++){
        printk("base addr:0x%x%x length:0x%x%x \n",mmap->base_addr_high,mmap->base_addr_low,mmap->length_high,mmap->length_low);
    }
}

void init_pmm(){
    //物理内存起始位置
    mmap_entry_t *mmap_start_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr;
    //物理内存结束位置
    mmap_entry_t *mmap_end_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr + glb_mboot_ptr->mmap_length;

    mmap_entry_t *map_entry;
    //遍历每块内存
    for(map_entry = mmap_start_addr;map_entry<mmap_end_addr;map_entry++){
        //如果类型为1，并且在1m以上
        if(map_entry->type == 1 && map_entry->base_addr_low == 0x100000){
            //内核页地址是
            uint32_t page_addr = map_entry->base_addr_low + (uint32_t)(kern_end-kern_start);
            //
            uint32_t length = map_entry->base_addr_low + map_entry->length_low;
            while(page_addr < length && page_addr <= PMM_MAX_SIZE){
                pmm_free_page(page_addr);
                page_addr += PMM_PAGE_SIZE;
                phy_page_count++;
            }
        }
    }
    //
    
}
uint32_t pmm_alloc_page(){
        assert(pmm_stack_top!=0,"out of memory!");
        uint32_t page = pmm_stack[pmm_stack_top--];
        return page;
    }
void pmm_free_page(uint32_t p){
    assert(pmm_stack_top!= PAGE_MAX_SIZE,"out of pmm_stack stack!");
    pmm_stack[++pmm_stack_top] = p;
}