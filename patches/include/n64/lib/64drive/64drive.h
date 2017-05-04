#ifndef _N64_LIB_64DRIVE_H_
#define _N64_LIB_64DRIVE_H_

extern "C" {

#define CMD_READ_SECTOR_TO_BUF     0x01 //param: LBA
#define CMD_READ_SECTORS_TO_SDRAM  0x03 //param: LBA, RAMADDR, N_SECTORS
#define CMD_WRITE_BUF_TO_SECTOR    0x10 //param: LBA
#define CMD_WRITE_SDRAM_TO_SECTORS 0x13 //param: LBA, RAMADDR, N_SECTORS
#define CMD_SET_SAVE_TYPE          0xD0 //param: SAVE_TYPE
#define CMD_DISABLE_SAVE_WBK       0xD1 //disable save writeback
#define CMD_ENABLE_SAVE_WBK        0xD2 //enable save writeback
#define CMD_DISABLE_LOAD_BSWAP     0xE0 //disable byteswap on load
#define CMD_ENABLE_LOAD_BSWAP      0xE1 //enable byteswap on load
#define CMD_ENABLE_ROM_WRITE       0xF0 //enable write to cart ROM
#define CMD_DISABLE_ROM_WRITE      0xF1 //disable write to cart ROM
#define CMD_START_FW_UPGRADE       0xFA //param: MAGIC (0x55504752)
#define CMD_SET_CF_PULSE_WIDTH     0xFD //param: N_CYCLES

#define SDRV_REG_BUFFER            0
#define SDRV_REG_STATUS            0x200 //u16 R-
#define SDRV_REG_COMMAND           0x208 //u32 -W
#define SDRV_REG_LBA               0x210 //u32 -W
#define SDRV_REG_LENGTH            0x218 //u32 RW
#define SDRV_REG_SDRAM_SIZE        0x2E8 //u32 R-
#define SDRV_REG_MAGIC             0x2EC //u32 R-
#define SDRV_REG_VARIANT           0x2F0 //u32 R-
#define SDRV_REG_PERSIST           0x2F4 //u32 RW
#define SDRV_REG_BUTTON            0x2F8 //u16 R-
#define SDRV_REG_UPGRADE_STATUS    0x2FA //u16 R-
#define SDRV_REG_REVISION          0x2FC //u16 R-

typedef enum {
    SDRV_SAVE_TYPE_NONE = 0,
    SDRV_SAVE_TYPE_EEPROM_4K,  //4kbit
    SDRV_SAVE_TYPE_EEPROM_16K, //16kbit
    SDRV_SAVE_TYPE_SRAM_256K,  //256kbit
    SDRV_SAVE_TYPE_FLASH_1M,   //1mbit
    SDRV_SAVE_TYPE_SRAM_768K,  //only used by Dezaemon 3D
    SDRV_SAVE_TYPE_POKEMON,    //special case for Pokemon Stadium 2
    SDRV_NUM_SAVE_TYPES
} sdrv_saveType;

#define DPRINT_BUF_SIZE (1024 - sizeof(u32))
#define DPRINT_NUM_BUFFERS 16
#define DPRINT_BUF_ADDR 0xB3000000

u32   sdrv_readReg(u32 addr);
void  sdrv_writeReg(u32 addr, u32 val);
int   sdrv_isBusy();
void  sdrv_setRomWritable(int write);
void  sdrv_init();
void  sdrv_setSaveType(int type);
void  sdrv_setSaveWriteback(int enable);
void  sdrv_setByteswap(int enable);
u16   sdrv_isButtonPressed();
void  sdrv_readSector(u32 sector);
void  sdrv_readSectors(u32 sector, u32 nSectors, void *dest);
void  sdrv_writeSector(u32 sector);
void  sdrv_writeSectors(u32 sector, u32 nSectors, const void *src);
void  sdrv_dprint(const char *text);

} //extern "C"
#endif //_N64_LIB_64DRIVE_H_
