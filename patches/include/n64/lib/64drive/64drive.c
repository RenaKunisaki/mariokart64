#include <n64.h>
extern "C" {

static volatile u32 *sdrv_regs = (volatile u32*)0xB8000000;
//static volatile u16 *eeprom = (volatile u16*)0xB8001000;
//static volatile u32 *save_writeback_lba = (volatile u32*)0xB8001800;

typedef struct {
    u32 serial;
    char data[DPRINT_BUF_SIZE];
} dprint_buf_s;
static dprint_buf_s *dprint_buf = (dprint_buf_s*)DPRINT_BUF_ADDR;
static uint32_t dprint_next_serial = 0;


int sdrv_init() {
    //Initialize 64drive. return nonzero on success, zero on failure.
    u32 intMask = __osDisableInt();
    while(dma_busy() || sdrv_isBusy());

    if(sdrv_readReg(SDRV_REG_MAGIC) != SDRV_MAGIC) {
        //not 64drive
        __osRestoreInt(intMask);
        return 0;
    }

    //clear dprint buffer region
    sdrv_setRomWritable(1);
    volatile u32 *p = (volatile u32*)DPRINT_BUF_ADDR;
    for(int i=0; i<(DPRINT_BUF_SIZE+4) * DPRINT_NUM_BUFFERS; i += 4) {
        cart_write32((void*)p++, 0);
    }
    sdrv_setRomWritable(0);
    __osRestoreInt(intMask);
    return 1;
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

u32 sdrv_getRamSize() {
    //Return number of bytes of SDRAM installed.
    return sdrv_readReg(SDRV_REG_SDRAM_SIZE);
}

u32 sdrv_getVariant() {
    //Return 64drive hardware variant. eg 0x00004100 = rev A
    return sdrv_readReg(SDRV_REG_VARIANT);
}

u32 sdrv_getVersion() {
    //Return 64drive firmware version. eg (decimal) 203 = 2.03
    return sdrv_readReg(SDRV_REG_REVISION);
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

void sdrv_setSaveType(int type) {
    //Set 64drive save type
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_BUFFER, type);
    sdrv_writeReg(SDRV_REG_COMMAND, CMD_SET_SAVE_TYPE);
    while(sdrv_isBusy());
}

void sdrv_setSaveWriteback(int enable) {
    //Set whether to periodically write save data back to memory card.
    //Default: on if booted from menu, off in USB mode.
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_COMMAND,
        enable ? CMD_ENABLE_SAVE_WBK : CMD_DISABLE_SAVE_WBK);
    while(sdrv_isBusy());
}

void sdrv_setByteswap(int enable) {
    //Set whether to byteswap data copied from memory card to SDRAM.
    //Default: disabled.
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_COMMAND,
        enable ? CMD_ENABLE_LOAD_BSWAP : CMD_DISABLE_LOAD_BSWAP);
    while(sdrv_isBusy());
}

u16 sdrv_isButtonPressed() {
    //Check if the button on the 64drive cartridge is pressed.
    return sdrv_readReg(SDRV_REG_BUTTON) & 0xFFFF;
}

void sdrv_readSector(u32 sector) {
    //Read sector from memory card into buffer (SDRV_REG_BUFFER).
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_LBA, sector);
    sdrv_writeReg(SDRV_REG_COMMAND, CMD_READ_SECTOR_TO_BUF);
    while(sdrv_isBusy());
}

void sdrv_readSectors(u32 sector, u32 nSectors, void *dest) {
    //Read multiple sectors from memory card into SDRAM.
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_LBA, sector);
    sdrv_writeReg(SDRV_REG_LENGTH, nSectors);
    sdrv_writeReg(SDRV_REG_BUFFER, ((u32)dest) & 0x01FFFFFF);
    sdrv_writeReg(SDRV_REG_COMMAND, CMD_READ_SECTORS_TO_SDRAM);
    while(sdrv_isBusy());
}

void sdrv_writeSector(u32 sector) {
    //Write sector from buffer (SDRV_REG_BUFFER) to memory card.
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_LBA, sector);
    sdrv_writeReg(SDRV_REG_COMMAND, CMD_WRITE_BUF_TO_SECTOR);
    while(sdrv_isBusy());
}

void sdrv_writeSectors(u32 sector, u32 nSectors, const void *src) {
    //Write multiple sectors to memory card from SDRAM.
    while(sdrv_isBusy());
    sdrv_writeReg(SDRV_REG_LBA, sector);
    sdrv_writeReg(SDRV_REG_LENGTH, nSectors);
    sdrv_writeReg(SDRV_REG_BUFFER + 4, ((u32)src) & 0x01FFFFFF);
    sdrv_writeReg(SDRV_REG_COMMAND, CMD_WRITE_SDRAM_TO_SECTORS);
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
        //return;
        osYieldThread();
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
