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
