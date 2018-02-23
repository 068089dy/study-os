#include "console.h"
#include "vargs.h"
#include "elf.h"



//
void init_debug();
void panic(const char *msg);
void print_cur_status();

void printk(const char *formet,...);
void printk_color(real_color_t back,real_color_t fore,const char *format,...);