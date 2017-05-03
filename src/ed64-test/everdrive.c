#include "everdrive.h"
extern "C" {
static volatile u32 *regs_ptr = (u32*)0xA8040000;

struct pi_regs_s {
    volatile void *ram_addr; //uncached RAM address of data
    volatile u32 pi_addr; //peripheral address
    volatile u32 read_len; //transfer length RAM -> periph
    volatile u32 write_len; //transfer length RAM <- periph
    volatile u32 status;
};
struct pi_regs_s *pi_regs = (struct pi_regs_s*)0xA4600000;

extern s32 osPiRawStartDma(s32 direction, u32 devAddr, void *vAddr, u32 nBytes);
extern void osYieldThread();
extern void *currentThread;
extern u32 __osDisableInt();
extern void __osRestoreInt(u32);
extern void osInvalDCache(void *vaddr, s32 nbytes);
extern void osWritebackDCache(void *vaddr, s32 nbytes); //unknown address
extern void osWriteBackDCacheAll();


void evd_setreg(u32 reg, u32 val) {
    volatile u8 dummy = regs_ptr[0];
    MEMORY_BARRIER();
    regs_ptr[reg] = val;
    MEMORY_BARRIER();
}

void evd_unlock() {
    evd_setreg(REG_KEY, 0x1234);
}

void evd_lock() {
    evd_setreg(REG_KEY, 0);
}


u32 dma_busy() {
    return pi_regs->status & 3;
}


void dma_to_cart(volatile void *src, volatile void *dest, u32 len) {
    u32 sa = (u32)src;
    u32 da = (u32)dest;
    pi_regs->ram_addr = (volatile void*)(sa & 0xFFFFFF); //to uncached
    MEMORY_BARRIER();
    pi_regs->pi_addr  = (da | 0x10000000) & 0x1FFFFFFF;
    MEMORY_BARRIER();
    pi_regs->read_len = len - 1;
    MEMORY_BARRIER();
    while(dma_busy());
}


void evd_dprint(volatile char *text, u32 len) {
    u32 ram_buff_addr = ED_DMA_BUFF_ADDR / 2048;

    #if 0
    //osWritebackDCache((void*)text, len); //XXX find this function in MK64
    osWriteBackDCacheAll();
    #else
    asm volatile(
        "1:               \n"
        "cache 0x19, (%0) \n"
        "addiu %1, %1, -4 \n"
        "bnez  %1, 1b     \n"
        "addiu %0, %0, 4  \n"
        : /* outputs (none) */
        : "r"(text), "r"(len) /* inputs */
        : "memory"
    );
    #endif

    //wait for DMA ready
    /* while(regs_ptr[REG_STATUS] & ED_STATE_DMA_BUSY) {
        osYieldThread();
    } */
    u32 intMask = __osDisableInt();
    while(dma_busy());

    //evd_unlock();
    //evd_setreg(REG_CFG, 1 << ED_CFG_SDRAM_ON);
    //evd_setreg(REG_SPI_CFG,
    //    (0 << SPI_CFG_SPD0) | (1 << SPI_CFG_SPD1) | (1 << SPI_CFG_SS));

    //why doesn't this work!?
    //dma_to_cart((volatile void*)text,
    //    (volatile void*)(ED_ROM_ADDR + ED_DMA_BUFF_ADDR), 512);

    volatile u32 *src = (volatile u32*)text;
    volatile u32 *dst = (volatile u32*)(ED_ROM_ADDR + ED_DMA_BUFF_ADDR);
    for(int i=0; i<512/4; i++) {
        *dst++ = *src++;
    }

    evd_setreg(REG_DMA_LEN, 0); //# 512-byte blocks - 1
    evd_setreg(REG_DMA_RAM_ADDR, ram_buff_addr);
    //evd_setreg(REG_DMA_RAM_ADDR, 0);
    evd_setreg(REG_DMA_CFG, DCFG_RAM_TO_FIFO);
    while(regs_ptr[REG_STATUS] & (ED_STATE_DMA_BUSY | ED_STATE_DMA_TOUT));
    //while(!(regs_ptr[REG_STATUS] & ED_STATE_TXE));

    evd_setreg(REG_DMA_LEN, 0);
    evd_setreg(REG_DMA_RAM_ADDR, ram_buff_addr);
    evd_setreg(REG_DMA_CFG, DCFG_FIFO_TO_RAM);
    while(regs_ptr[REG_STATUS] & (ED_STATE_DMA_BUSY | ED_STATE_DMA_TOUT));

    //evd_setreg(REG_CFG, 0);
    //evd_lock();
    __osRestoreInt(intMask);
}


} //extern "C"
