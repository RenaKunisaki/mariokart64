#ifndef _N64_LIB_RAWIO_H_
#define _N64_LIB_RAWIO_H_

extern "C" {

extern pi_regs_s *pi_regs;
void cart_write32(void *dest, u32 val);
u32 dma_busy();
void dma_to_cart(volatile void *src, volatile void *dest, u32 len);
void* memcpy_to_cart(void *dest, const void *src, u32 len);
void cache_writeback(void *buf, u32 len);

} //extern "C"
#endif //_N64_LIB_RAWIO_H_
