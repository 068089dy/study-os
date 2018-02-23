/*#include "string.h"

void memcpy(uint8_t *dest,const uint8_t *src,uint32_t len){
    for(;len!=0;len--){
        *dest++ = *src++;
    }
}

void memset(void *dest,uint8_t val,uint32_t len){
    uint8_t *dst = (uint8_t *)dest;
    for(;len!=0;len--){
        *dst++ = val;
    }
}

void bzero(void *dest,uint32_t len){
    memset(dest,0,len);
}

int strcmp(const char *str1,const char *str2){
    while(*str1 & *str2 & *str1==*str2){
        str1++;
        str2++;
    }
    return *str1-*str2;
}
/*
char *strcpy(char *dest,const char *src){
    for(;len!=0;len--){
        b[len] = a[len];
      }
}

char *strcat(char *dest,const char *src){

}
*/
/*
int strlen(const char *src){
    const char * eos = src;
    while(*eos++);
    return eos-src-1;
}
*/