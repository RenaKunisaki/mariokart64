#ifndef _N64_LIB_64DRIVE_H_
#define _N64_LIB_64DRIVE_H_

extern "C" {

typedef volatile struct {
    u16 buffer[256];    //RW 0000
    u16 status;         //R- 0200
    u32 command;        //-W 0208
    u32 lba;            //-W 0210
    u32 length;         //RW 0218
} __attribute__ ((aligned (8))) sixtyfourdrive_cmd_regs; //at 0x1800 0000

typedef volatile struct {
    u32 sdram_size;     //R- 02E8
    u32 hw_magic;       //R- 02EC
    u32 hw_variant;     //R- 02F0
    u32 persist_var;    //RW 02F4
    u16 button;         //R- 02F8
    u16 upgrade_status; //R- 02FA
    u16 revision;       //R- 02FC
} sixtyfourdrive_hw_regs; //at 0x1800 02E8

#define CMD_READ_SECTOR_TO_BUF     0x01
#define CMD_READ_SECTORS_TO_SDRAM  0x03
#define CMD_WRITE_BUF_TO_SECTOR    0x10
#define CMD_WRITE_SDRAM_TO_SECTORS 0x13
#define CMD_SET_SAVE_TYPE          0xD0
#define CMD_DISABLE_SAVE_WBK       0xD1 //disable save writeback
#define CMD_ENABLE_SAVE_WBK        0xD2 //enable save writeback
#define CMD_DISABLE_LOAD_BSWAP     0xE0 //disable byteswap on load
#define CMD_ENABLE_LOAD_BSWAP      0xE1 //enable byteswap on load
#define CMD_ENABLE_ROM_WRITE       0xF0 //enable write to cart ROM
#define CMD_DISABLE_ROM_WRITE      0xF1 //disable write to cart ROM
#define CMD_START_FW_UPGRADE       0xFA
#define CMD_SET_CF_PULSE_WIDTH     0xFD
/*
extern s32 osPiRawStartDma(s32 direction, u32 devAddr, void *vAddr, u32 nBytes);
extern void osYieldThread();
extern void *currentThread;
extern u32 __osDisableInt();
extern void __osRestoreInt(u32);
extern void osInvalDCache(void *vaddr, s32 nbytes);
extern void osWritebackDCache(void *vaddr, s32 nbytes); //unknown address
extern void osWriteBackDCacheAll();
*/

void cart_write32(void *dest, u32 val);
void* memcpy_to_cart(void *dest, const void *src, u32 len);
void cache_writeback(void *buf, u32 len);
u32 dma_busy();
u32 sdrv_read32(u32 addr);
void sdrv_write32(u32 addr, u32 val);
int sdrv_isBusy();
void sdrv_setRomWritable(int write);
void sdrv_init();
void sdrv_dprint(const char *text);

} //extern "C"
#endif //_N64_LIB_64DRIVE_H_
