#ifndef _N64_LIB_LIBC_H_
#define _N64_LIB_LIBC_H_

extern "C" {

void* memcpy(void *dest, const void *src, u32 len);
void* memset(void *dest, u32 data, u32 len);

} //extern "C"
#endif //_N64_LIB_LIBC_H_
