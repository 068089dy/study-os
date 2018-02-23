#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"
typedef enum real_color{
    rc_black = 0,
    rc_white = 15,
    rc_blue = 1,
}real_color_t;
//清屏
void console_clear();
//输出一个字符
void console_putc_color(char c,real_color_t back,real_color_t fore);
//打印字符串
void console_write(char *cstr);
//打印带颜色的字符串
void console_write_color(char *cstr,real_color_t back,real_color_t fore);
//打印16进制整数
void console_write_hex(uint32_t,real_color_t back,real_color_t fore);
//打印10进制整数
void console_write_dec(uint32_t n,real_color_t back,real_color_t fore);
#endif