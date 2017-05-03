#include "../mk64/mk64.h"
#include "64drive.h"
extern "C" {

extern void osWriteBackDCacheAll();
extern u32 osGetThreadId(void*);
extern void osYieldThread();
extern void *currentThread;

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

static volatile char text[512];
void dma_to_cart(volatile void *src, volatile void *dest, u32 len);


void init() {
    sdrv_setRomWritable(1);
    volatile u32 *p = (volatile u32*)0xB3000000;
    for(int i=0; i<16*1024; i += 4)
        *p++ = 0;
    osWriteBackDCacheAll();
    sdrv_setRomWritable(0);
}


void do_hex_view(u16 buttons, u16 held) {
    char *buf;
    static u32 addr = 0xB3000000;
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
    if(buttons & BUTTON_Z    ) addr ^= 0xA0000000;
    if(buttons & BUTTON_C_LEFT) { //DMA to cart
        dma_to_cart((volatile void*)"DMA test",
            (volatile void*)(0xB3000000), 512);
    }
    if(buttons & BUTTON_C_RIGHT) { //dprint
        sdrv_dprint("hello world\n");
        // *((u32*)0xB0000020) = 0x41424344;
    }
    if(buttons & BUTTON_C_UP) { //set writable
        sdrv_setRomWritable(1);
    }
    if(buttons & BUTTON_C_DOWN) { //set not writable
        sdrv_setRomWritable(0);
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

    do_hex_view(newButtons, buttons);
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

    //sdrv_dprint(text, buf - text);
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
