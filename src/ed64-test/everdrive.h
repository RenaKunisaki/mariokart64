#include "../n64/n64.h"
extern "C" {
#define REG_CFG 0
#define REG_STATUS 1
#define REG_DMA_LEN 2
#define REG_DMA_RAM_ADDR 3
#define REG_MSG 4
#define REG_DMA_CFG 5
#define REG_SPI 6
#define REG_SPI_CFG 7
#define REG_KEY 8
#define REG_SAV_CFG 9
#define REG_SEC 10
#define REG_VER 11

#define REG_CFG_CNT 16
#define REG_CFG_DAT 17
#define REG_MAX_MSG 18
#define REG_CRC 19

#define DCFG_SD_TO_RAM 1
#define DCFG_RAM_TO_SD 2
#define DCFG_FIFO_TO_RAM 3
#define DCFG_RAM_TO_FIFO 4

#define ED_STATE_DMA_BUSY 0
#define ED_STATE_DMA_TOUT 1
#define ED_STATE_TXE 2
#define ED_STATE_RXF 3
#define ED_STATE_SPI 4

#define SPI_CFG_SPD0 0
#define SPI_CFG_SPD1 1
#define SPI_CFG_SS 2
#define SPI_CFG_RD 3
#define SPI_CFG_DAT 4
#define SPI_CFG_1BIT 5

#define ED_CFG_SDRAM_ON 0
#define ED_CFG_SWAP 1
#define ED_CFG_WR_MOD 2
#define ED_CFG_WR_ADDR_MASK 3

#define ED_STATE_DMA_BUSY 0
#define ED_STATE_DMA_TOUT 1
#define ED_STATE_TXE 2
#define ED_STATE_RXF 3
#define ED_STATE_SPI 4

#define ED_ROM_LEN  0x4000000
#define ED_ROM_ADDR 0xb0000000
#define ED_ROM_END_ADDR (0xb0000000 + 0x4000000)
#define ED_DMA_BUFF_ADDR (ED_ROM_LEN - 0x100000)

#define EVD_ERROR_FIFO_TIMEOUT 90;
#define EVD_ERROR_MMC_TIMEOUT 91;

#define BOOT_UPD_ERR_WRONG_SIZE 95
#define BOOT_UPD_ERR_HDR 96
#define BOOT_UPD_ERR_CMP 97
#define BOOT_UPD_ERR_CIC_DTCT 98

#define FAT_ERR_NOT_EXIST 100
#define FAT_ERR_EXIST 101
#define FAT_ERR_NAME 102
#define FAT_ERR_OUT_OF_FILE 103
#define FAT_ERR_BAD_BASE_CLUSTER 104;
#define FAT_ERR_NO_FRE_SPACE 105
#define FAT_ERR_NOT_FILE 106
#define FAT_ERR_FILE_MODE 107
#define FAT_ERR_ROT_OVERFLOW 108
#define FAT_ERR_OUT_OF_TABLE 109
#define FAT_ERR_INIT 110
#define FAT_LFN_BUFF_OVERFLOW 111
#define FAT_DISK_NOT_READY 112
#define FAT_ERR_SIZE 113
#define FAT_ERR_RESIZE 114

#define ERR_FILE8_TOO_BIG 140
#define ERR_FILE16_TOO_BIG 141
#define ERR_WRON_OS_SIZE 142
#define ERR_OS_VERIFY 143
#define ERR_OS_VERIFY2 144
#define ERR_EMU_NOT_FOUND 145
#define ERR_SAVE_FORMAT 146
#define ERR_EEPROM 147
#define ERR_NO_FAV_SPACE 150

void evd_setreg(u32 reg, u32 val);
void evd_unlock();
void evd_lock();
void evd_dprint(volatile char *text, u32 len);

} //extern "C"
