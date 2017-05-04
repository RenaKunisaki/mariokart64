#ifndef _MAIN_H_
#define _MAIN_H_

#include "../mk64/mk64.h"
extern "C" {
    extern const char *hex;
    extern OSThread *currentThread;

    char* strAppend(char *dest, const char *src);
    char* printHex(char *buf, u32 num, int nDigits);
    char* printNum(char *buf, u32 num);
} //extern "C"

#endif //_MAIN_H_
