#include <n64.h>
extern "C" {

static volatile u32 *sdrv_regs = (volatile u32*)0xB8000000;
//static volatile u16 *eeprom = (volatile u16*)0xB8001000;
//static volatile u32 *save_writeback_lba = (volatile u32*)0xB8001800;

#define DPRINT_BUF_SIZE (1024 - sizeof(u32))
#define DPRINT_NUM_BUFFERS 16
#define DPRINT_BUF_ADDR 0xB3000000

typedef struct {
    u32 serial;
    char data[DPRINT_BUF_SIZE];
} dprint_buf_s;
static dprint_buf_s *dprint_buf = (dprint_buf_s*)DPRINT_BUF_ADDR;
static uint32_t dprint_next_serial = 0;


void sdrv_init() {
    //Initialize 64drive
    u32 intMask = __osDisableInt();
    while(dma_busy() || sdrv_isBusy());
    sdrv_setRomWritable(1);

    //clear dprint buffer region
    volatile u32 *p = (volatile u32*)DPRINT_BUF_ADDR;
    for(int i=0; i<(DPRINT_BUF_SIZE+4) * DPRINT_NUM_BUFFERS; i += 4) {
        cart_write32((void*)p++, 0);
    }

    sdrv_setRomWritable(0);
    __osRestoreInt(intMask);
}

int sdrv_isBusy() {
    //check if 64drive is busy
    return sdrv_readReg(SDRV_REG_STATUS) & BIT(12);
}

u32 sdrv_readReg(u32 reg) {
    //read from 64drive register
    return sdrv_regs[reg / 4];
}

void sdrv_writeReg(u32 reg, u32 val) {
    //write to 64drive register
    cart_write32((void*)&sdrv_regs[reg / 4], val);
}

void sdrv_setRomWritable(int write) {
    //Set whether cartridge ROM is writable from N64.
    while(sdrv_isBusy());
    MEMORY_BARRIER();
    sdrv_writeReg(SDRV_REG_COMMAND,
        write ? CMD_ENABLE_ROM_WRITE : CMD_DISABLE_ROM_WRITE);
    MEMORY_BARRIER();
    while(sdrv_isBusy());
}

void sdrv_dprint(const char *text) {
    //debug print to 64drive USB port
    //requires host program listening on PC, otherwise does nothing
    static volatile dprint_buf_s buf __attribute__ ((aligned (16)));

    //XXX handle text longer than DPRINT_BUF_SIZE
    memcpy((void*)buf.data, text, DPRINT_BUF_SIZE);
    buf.serial = 0xFFFFFFFF;
    cache_writeback((void*)&buf, DPRINT_BUF_SIZE);

    //u32 intMask = __osDisableInt();
    //while(dma_busy() || sdrv_isBusy());

    //scan the slots for a free one.
    int bufIdx = 0;
    while(1) {
        for(bufIdx=0; bufIdx < DPRINT_NUM_BUFFERS; bufIdx++) {
            if(!dprint_buf[bufIdx].serial) break;
        }
        if(bufIdx < DPRINT_NUM_BUFFERS) break;

        //no free buffer... wait for one
        //__osRestoreInt(intMask);
        return;
        //osYieldThread();
        //intMask = __osDisableInt();
        //while(dma_busy() || sdrv_isBusy());
    }

    u32 intMask = __osDisableInt();

    //write text to buffer
    sdrv_setRomWritable(1);

    //copy text into free slot, but don't mark slot as full yet.
    //using DMA here freezes the game, probably because it panics upon
    //receiving an unexpected DMA-complete signal, or just my code is bad.
    //dma_to_cart((volatile void*)&buf,
    //    (volatile void*)(&dprint_buf[bufIdx].serial), DPRINT_BUF_SIZE);
    memcpy_to_cart(&dprint_buf[bufIdx], (const void*)&buf, DPRINT_BUF_SIZE);
    MEMORY_BARRIER();

    //now that buffer is actually filled, mark as full.
    //host should eventually poll for it.
    cart_write32(&dprint_buf[bufIdx].serial, ++dprint_next_serial);
    MEMORY_BARRIER();

    sdrv_setRomWritable(0);
    __osRestoreInt(intMask);
}


} //extern "C"
