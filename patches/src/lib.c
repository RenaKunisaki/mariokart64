#include "main.h"
const char *hex = "0123456789ABCDEF";


char* strAppend(char *dest, const char *src) {
    //same as strcpy, but returns pointer to end of string.
    while(*dest++ = *src++);
    return dest-1;
}


char* printHex(char *buf, u32 num, int nDigits) {
    //print hex number into buffer.
    //will truncate numbers larger than specified length.
    //returns pointer to null terminator.
    char *bufEnd = &buf[nDigits];
    *bufEnd = 0;
    while(nDigits--) {
        buf[nDigits] = hex[num & 0xF];
        num >>= 4;
    }
    return bufEnd;
}


char* printNum(char *buf, u32 num) {
    //print decimal number into buffer.
    //returns pointer to null terminator.
    char digits[16];
    char *d = digits;
    *d = '0';
    while(num > 0) {
        *d++ = hex[num % 10];
        num /= 10;
    }

    do {
        *buf++ = *--d;
    } while(d != digits);

    *buf = 0;
    return buf;
}
