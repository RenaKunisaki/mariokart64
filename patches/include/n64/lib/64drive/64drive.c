#include <n64.h>
extern "C" {

static sixtyfourdrive_cmd_regs *cmd_regs = (sixtyfourdrive_cmd_regs*)0xB8000000;
static sixtyfourdrive_hw_regs  *hw_regs  = (sixtyfourdrive_hw_regs*)0xB80002E8;
static u16 *eeprom = (u16*)0xB8001000;
static u32 *save_writeback_lba = (u32*)0xB8001800;

#define DPRINT_BUF_SIZE (1024 - sizeof(u32))
#define DPRINT_NUM_BUFFERS 16
#define DPRINT_BUF_ADDR 0xB3000000
typedef struct {
    u32 serial;
    char data[DPRINT_BUF_SIZE];
} dprint_buf_s;
static dprint_buf_s *dprint_buf = (dprint_buf_s*)DPRINT_BUF_ADDR;
static uint32_t dprint_next_serial = 0;


u32 sdrv_read32(u32 addr) {
    return *((volatile u32*)(addr | 0xB8000000));
}

void sdrv_write32(u32 addr, u32 val) {
    cart_write32((void*)(addr | 0xB8000000), val);
}

int sdrv_isBusy() {
    return sdrv_read32(0x0200) & BIT(12);
}

void sdrv_setRomWritable(int write) {
    //Set whether cartridge ROM is writable from N64.
    while(sdrv_isBusy());
    MEMORY_BARRIER();
    sdrv_write32(0x0208, write ? CMD_ENABLE_ROM_WRITE : CMD_DISABLE_ROM_WRITE);
    MEMORY_BARRIER();
    while(sdrv_isBusy());
}

void sdrv_init() {
    u32 intMask = __osDisableInt();
    while(dma_busy() || sdrv_isBusy());
    sdrv_setRomWritable(1);

    //clear buffer region
    volatile u32 *p = (volatile u32*)DPRINT_BUF_ADDR;
    for(int i=0; i<(DPRINT_BUF_SIZE+4) * DPRINT_NUM_BUFFERS; i += 4) {
        cart_write32((void*)p++, 0);
    }

    sdrv_setRomWritable(0);
    __osRestoreInt(intMask);
}

void sdrv_dprint(const char *text) {
    static volatile dprint_buf_s buf __attribute__ ((aligned (16)));

    //XXX handle text longer than DPRINT_BUF_SIZE
    memcpy((void*)buf.data, text, DPRINT_BUF_SIZE);
    buf.serial = dprint_next_serial | 0x80000000;
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
    //asm volatile("break");

    //write text to buffer
    sdrv_setRomWritable(1);

    //copy text into free slot, but don't mark slot as full yet
    //dma_to_cart((volatile void*)&buf,
    //    (volatile void*)(&dprint_buf[bufIdx].serial), DPRINT_BUF_SIZE);
    memcpy_to_cart(&dprint_buf[bufIdx], (const void*)&buf, DPRINT_BUF_SIZE);
    MEMORY_BARRIER();

    //now that buffer is actually filled, mark as full.
    //host should eventually poll for it.
    cart_write32(&dprint_buf[bufIdx].serial, dprint_next_serial);
    dprint_next_serial = (dprint_next_serial + 1) & 0x7FFFFFFF;
    MEMORY_BARRIER();

    sdrv_setRomWritable(0);
    __osRestoreInt(intMask);
}


} //extern "C"
