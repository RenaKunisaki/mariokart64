#include <n64.h>

void* memcpy(void *dest, const void *src, u32 len) {
    //XXX handle non-multiple-of-4 length, non-aligned dest
    volatile u32 *d = (volatile u32*)dest;
    volatile u32 *s = (volatile u32*)src;
    for(u32 i=0; i<len; i += 4) {
        *d++ = *s++;
    }
    return dest;
}

void* memset(void *dest, u32 data, u32 len) {
    //XXX handle non-multiple-of-4 length, non-aligned dest
    volatile u32 *d = (volatile u32*)dest;
    for(int i=0; i<len/4; i++) *d++ = data;
    return dest;
}
