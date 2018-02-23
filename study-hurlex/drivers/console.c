#include "types.h"
#include "console.h"
//vga显示缓冲的起点0xB8000
static uint16_t *video_memory = (uint16_t *)0xB8000;

//光标坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//移动光标
static void move_cursor(){
    //
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;

    outb(0x3D4,14);//设置光标高字节
    outb(0x3d5,cursorLocation >> 8);//发送高八位
    outb(0x3d4,15);//设置光标低字节
    outb(0x3d5,cursorLocation);//发送低8位
}

//清屏(用白底黑字的"空格符"覆盖整个屏幕的显示区域)
void console_clear(){
    //属性字节：白字黑底
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    //0x20:空格asicc码
    uint16_t blank = 0x20 | (attribute_byte << 8);

    int i;
    for(i = 0;i<80*25;i++){
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}
//屏幕滚动(将后24行上移一行，最后一行清空)
static void scroll(){
    //属性字节：白字黑底
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    //0x20:空格asicc码
    uint16_t blank = 0x20 | (attribute_byte << 8);

    if(cursor_y>=25){
        //上移一行
        for(int i = 0;i<24*80;i++){
            video_memory[i] = video_memory[i+80];
        }
        //最后一行清空
        for(int i = 24*80;i<25*80;i++){
            video_memory[i] = blank;
        }
        cursor_y = 24;
    }
}
//输出一个字符
void console_putc_color(char c,real_color_t back,real_color_t fore){
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;

    //0x08:backspace;0x09:tab.
    //若退格且光标不在行首，光标退格.
    if(c == 0x08 && cursor_x){
        cursor_x--;
    }
    //若tab
    else if(c == 0x09){
        cursor_x = (cursor_x+8) & ~(8-1);
    }
    //
    else if(c == '\r'){
        cursor_x = 0;
    }
    //若换行
    else if(c == '\n'){
        cursor_x = 0;
        cursor_y++;
    }
    //若空格
    else if(c >= ' '){
        video_memory[cursor_y*80 + cursor_x] = c | attribute;
        cursor_x++;
    }
    if(cursor_x >= 80){
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_cursor();
}
//打印字符串
void console_write(char *cstr){
    while(*cstr){
        console_putc_color(*cstr++,rc_black,rc_white);
    }
}

//打印带颜色的字符串
void console_write_color(char *cstr,real_color_t back,real_color_t fore){
    while(*cstr){
        console_putc_color(*cstr,back,fore);
    }
}
/*
//打印16进制整数
void console_write_hex(uint32_t,real_color_t back,real_color_t fore){

}
//打印10进制整数
void console_write_dec(uint32_t n,real_color_t back,real_color_t fore){

}*/