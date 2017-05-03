#include "everdrive.h"
#include "../mk64/mk64.h"
extern "C" {

extern u32 osGetThreadId(void*);
extern void osYieldThread();
extern void *currentThread;

static volatile u32 *ed64_reg = (volatile u32*)0xA8040000;
volatile u16 *player1_buttons = (volatile u16*)0x80196504;
static const char *hex = "0123456789ABCDEF";

char *strcpy_but_better(char *dest, const char *src) __attribute__((nonnull, returns_nonnull));
char *printHex(char *buf, u32 num, int nDigits) __attribute__((nonnull, returns_nonnull, used));


char *strcpy_but_better(char *dest, const char *src) {
    while(*dest++ = *src++);
    return dest-1;
}

void memset(void *dest, u32 data, u32 len) {
    u32 *d = (u32*)dest;
    for(int i=0; i<len/4; i++) *d++ = data;
}

char *printHex(char *buf, u32 num, int nDigits) {
    char *bufEnd = &buf[nDigits];
    while(nDigits--) {
        buf[nDigits] = hex[num & 0xF];
        num >>= 4;
    }
    return bufEnd;
}


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

static const char *regNames[] = {
    "    CFG",
    "   STAT",
    "DMA_LEN",
    "DMA_RAM",
    "    MSG",
    "DMA_CFG",
    "    SPI",
    "SPI_CFG",
    "    KEY",
    "SAV_CFG",
    "    SEC",
    "    VER",
    "     12",
    "     13",
    "     14",
    "     15",
    "CFG_CNT",
    "CFG_DAT",
    "MAX_MSG",
    "    CRC",
};
static volatile char text[512];
void dma_to_cart(volatile void *src, volatile void *dest, u32 len);

//DMA_BUF_ADDR = 0x03F00000


void do_ed64_test(u16 buttons, u16 held) {
    u32 *t = (u32*)text;
    for(int i=0; i<512/4; i++) {
        t[i] = 0xDEADBEEF;
        //text[i] = (char)i;
    }

    //char *buf = text;
    //buf = strcpy_but_better(buf, "DL ");
    //buf = printHex(buf, (u32)dlist, 8);
    //debugPrintStr(32, 0, text);

    evd_setreg(REG_CFG, 1 << ED_CFG_SDRAM_ON);
    //evd_setreg(REG_CFG, (1 << ED_CFG_SDRAM_ON) | (1 << ED_CFG_WR_ADDR_MASK));
    //evd_setreg(REG_SPI_CFG,
    //    (0 << SPI_CFG_SPD0) | (1 << SPI_CFG_SPD1) | (1 << SPI_CFG_SS));

    if(buttons & BUTTON_C_UP) {
        //send to host
        evd_setreg(REG_DMA_LEN, 0); //# 512-byte blocks - 1
        //evd_setreg(REG_DMA_RAM_ADDR, ram_buff_addr);
        evd_setreg(REG_DMA_RAM_ADDR, ED_DMA_BUFF_ADDR / 2048);
        evd_setreg(REG_DMA_CFG, DCFG_RAM_TO_FIFO);
    }
    if(buttons & BUTTON_C_DOWN) {
        //read from host
        evd_setreg(REG_DMA_LEN, 0); //# 512-byte blocks - 1
        evd_setreg(REG_DMA_RAM_ADDR, ED_DMA_BUFF_ADDR / 2048);
        evd_setreg(REG_DMA_CFG, DCFG_FIFO_TO_RAM);
    }
    if(buttons & BUTTON_C_LEFT) {
        dma_to_cart((volatile void*)text,
            (volatile void*)(ED_ROM_ADDR + ED_DMA_BUFF_ADDR), 512);
    }
    if(buttons & BUTTON_C_RIGHT) {
        strcpy_but_better((char*)text, "hello world");
        evd_dprint(text, 512);
    }

    char *buf = (char*)text;
    //buf = printHex(buf, i, 2);
    //buf = printHex(buf, *player1_buttons, 4);
    //*buf++ = '\0';
    //debugPrintStr(8, 0, text);

    for(int i=0; i<20; i++) {
        buf = (char*)text;
        //buf = printHex(buf, i, 2);
        buf = strcpy_but_better(buf, regNames[i]);
        buf = strcpy_but_better(buf, ": ");
        buf = printHex(buf, ed64_reg[i] >> 16, 4);
        *buf++ = ' ';
        buf = printHex(buf, ed64_reg[i] & 0xFFFF, 4);
        *buf++ = '\0';
        debugPrintStr(8, (9 * i) + 8, (char*)text);
    }

    volatile u32 *ptr = (volatile u32*)(ED_DMA_BUFF_ADDR + ED_ROM_ADDR);
    buf = (char*)text;
    buf = printHex(buf, (u32)ptr, 8);
    buf = strcpy_but_better(buf, ": ");
    buf = printHex(buf, *ptr, 8);
    *buf++ = '\0';
    debugPrintStr(8, (9 * 21) + 8, (char*)text);
    //evd_dprint(text, buf - text);
}

void do_hex_view(u16 buttons, u16 held) {
    char *buf;
    static u32 addr = 0xB3F00000;
    //static u32 addr = 0xA8040000;
    static int cursor = 7;

    u32 *t = (u32*)text;
    for(int i=0; i<512/4; i++) {
        t[i] = 0xDEADBEEF;
        //text[i] = (char)i;
    }

    if(buttons & BUTTON_UP   ) addr += (1 << ((7 - cursor) * 4));
    if(buttons & BUTTON_DOWN ) addr -= (1 << ((7 - cursor) * 4));
    if(buttons & BUTTON_LEFT ) cursor = (cursor - 1) & 7;
    if(buttons & BUTTON_RIGHT) cursor = (cursor + 1) & 7;
    if(buttons & BUTTON_L    ) addr -= 0x1000;
    if(buttons & BUTTON_R    ) addr += 0x1000;
    if(buttons & BUTTON_Z    ) addr ^= 0x80000000;
    if(buttons & BUTTON_C_UP) { //send to host
        evd_setreg(REG_DMA_LEN, 0); //# 512-byte blocks - 1
        //evd_setreg(REG_DMA_RAM_ADDR, ram_buff_addr);
        evd_setreg(REG_DMA_RAM_ADDR, ED_DMA_BUFF_ADDR / 2048);
        evd_setreg(REG_DMA_CFG, DCFG_RAM_TO_FIFO);
    }
    if(buttons & BUTTON_C_DOWN) { //read from host
        evd_setreg(REG_DMA_LEN, 0); //# 512-byte blocks - 1
        evd_setreg(REG_DMA_RAM_ADDR, ED_DMA_BUFF_ADDR / 2048);
        evd_setreg(REG_DMA_CFG, DCFG_FIFO_TO_RAM);
    }
    if(buttons & BUTTON_C_LEFT) { //DMA to cart
        dma_to_cart((volatile void*)"DMA test",
            (volatile void*)(ED_ROM_ADDR + ED_DMA_BUFF_ADDR), 512);
    }
    if(buttons & BUTTON_C_RIGHT) { //dprint
        evd_dprint((volatile char*)"hello world", 512);
    }

    //print address
    buf = (char*)text;
    buf = printHex(buf, addr, 8);
    *buf++ = '\0';
    debugPrintStr(0, 0, (char*)text);
    debugPrintStr(cursor * 8, -8, (char*)"v");

    //print data
    u32 *src = (u32*)(addr & ~3);
    for(int i=0; i<20; i++) {
        buf = (char*)text;
        buf = printHex(buf, ((u32)src) & 0xFFFF, 4);
        *buf++ = ':'; *buf++ = ' ';

        for(int j=0; j<2; j++) {
            u32 val = *src++;
            buf = printHex(buf, val >> 24, 2); *buf++ = ' ';
            buf = printHex(buf, val >> 16, 2); *buf++ = ' ';
            buf = printHex(buf, val >>  8, 2); *buf++ = ' ';
            buf = printHex(buf, val,       2); *buf++ = ' ';
            *buf++ = ' ';
        }

        *buf++ = '\0';
        debugPrintStr(0, (9 * i) + 8, (char*)text);
    }
}


void* titleHook(void *dlist, void **dest) {
    *dest = drawBox(dlist, 0, 0, 320, 240, 0, 0, 0, 0xB0);
    //debugNumberSignCheck = 0; //print unsigned; 0x0601 for signed
    debugLoadFont();

    static u16 prevButtons = 0;
    u16 buttons = *player1_buttons;
    u16 newButtons = buttons & ~prevButtons;
    prevButtons = buttons;

    evd_unlock();
    //do_ed64_test(buttons);
    do_hex_view(newButtons, buttons);
    evd_lock();
    titleDemoCounter = -999999999;

    return *dest;
}


static int running = 0;

void dmaThreadHook2(u32 direction, u32 devAddr, void *vAddr, u32 nBytes) {
    if(running) return;
    if(currentThread != (void*)0x80195270) return;
    running = 1;

    u32 *t = (u32*)text;
    for(int i=0; i<512/4; i++) {
        t[i] = 0xAAAAAAAA;
        //text[i] = (char)i;
    }

    char *buf = (char*)text;
    buf = strcpy_but_better(buf, "DMA ");
    buf = printHex(buf, devAddr, 6);
    *buf++ = ' ';
    *buf++ = direction ? '<' : '>';
    *buf++ = ' ';
    buf = printHex(buf, (u32)vAddr, 8);
    buf = strcpy_but_better(buf, " len ");
    buf = printHex(buf, nBytes, 8);
    buf = strcpy_but_better(buf, " T ");
    buf = printHex(buf, (u32)currentThread, 8);
    *buf++ = '\r';
    *buf++ = '\n';
    *buf++ = '\0';

    evd_dprint(text, buf - text);
    //evd_dprint(text, 512);
    running = 0;
}

//PATCH_JAL((void*)0x0A0584, doThing);
//PATCH_PTR((void*)0x0A0584, doThing);

//we need to also get .rodata into ROM...
//there must be a way to specify in the linkscript both the file offset
//and RAM address of a section?
//looks like the AT() directive.
//VMA is the RAM address, LMA is the ROM address
//so the ELF section list already contains all info needed to load from ROM to RAM.
//we might even be able to strip some unneeded sections and dump the ELF itself
//into the ROM file and write a small loader...
//but of course we still need to patch some code in to actually do the loading
//at some point.

//so the link script can specify where to place sections in the ROM file
//and where they expect to be loaded into RAM.
//we can use that to write them into ROM, and then load them whenever we
//decide to do so.
//for cases like this one, we're patching overtop of some existing code,
//so we don't need to load it into RAM, the game does that for us.
//we just need to make sure we specify the correct RAM address it loads to.

//from sections.txt:
//Idx Name          Size      VMA       LMA       File off  Algn  Flags
//0 .text         00000054  8009f984  000a0584  00001984  2**2  CONTENTS, ALLOC, LOAD, READONLY, CODE
//means copy 0x54 bytes from 0x1984 in the ELF file to 0xA0584 in the ROM file,
//and get it loaded to RAM at 0x8009F984.
//the AT command's description in the manual shows nice ways to do this.
//VMA = RAM address, LMA = ROM address

//unfortunately gcc doesn't appear to support the __naked__ attribute for MIPS.
//so we can't just use that to patch stuff.
//we'll still need to write a little stub in assembly, patch it into the ROM
//somewhere, and use it to load sections into RAM.
//that might be (or bootstrap) a simple ELF loader, since ELF gives us all the
//info we need (ROM addr, RAM addr, size, flags, entry point).
//then we just need to figure out where to insert that, and where and when to
//actually load and execute the ELF...

}; //extern "C"
