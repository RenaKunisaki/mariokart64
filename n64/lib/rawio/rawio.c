#include <n64.h>
extern "C" {

pi_regs_s *pi_regs = (pi_regs_s*)0xA4600000;

void cart_write32(void *dest, u32 val) {
    //write u32 to cartridge space
    while(dma_busy());
    *(u32*)dest = val;
}

u32 dma_busy() {
    //check if DMA/PI is busy
    return pi_regs->status & 3;
}

void dma_to_cart(volatile void *src, volatile void *dest, u32 len) {
    //DMA to cartridge space
    u32 sa = (u32)src;
    u32 da = (u32)dest;
    while(dma_busy());
    pi_regs->ram_addr = (volatile void*)(sa & 0xFFFFFF); //to uncached
    MEMORY_BARRIER();
    pi_regs->pi_addr  = (da | 0x10000000) & 0x1FFFFFFF;
    MEMORY_BARRIER();
    pi_regs->read_len = len - 1;
    MEMORY_BARRIER();
    while(dma_busy());
}

void* memcpy_to_cart(void *dest, const void *src, u32 len) {
    //memcpy to cartridge space
    u32 *d = (u32*)dest;
    u32 *s = (u32*)src;
    for(u32 i=0; i<len; i += 4) {
        cart_write32(d++, *s++);
    }
    //XXX handle non-multiple-of-4 length
    return dest;
}

void cache_writeback(void *buf, u32 len) {
    //write `len` bytes starting at `buf` back to physical memory from cache.
    #if 0
        //osWritebackDCache((void*)text, len); //XXX find this function in MK64
        osWriteBackDCacheAll();
    #else
        u32 _dummy0, _dummy1;
        asm volatile(
            "1:               \n"
            "cache 0x19, (%0) \n"
            "addiu %1, %1, -4 \n"
            "bnez  %1, 1b     \n"
            "addiu %0, %0, 4  \n"
            : "=r"(_dummy0), "=r"(_dummy1) /* outputs */
            : "0"(buf), "1"(len) /* inputs */
            : "memory"
        );
    #endif
}

} //extern "C"
