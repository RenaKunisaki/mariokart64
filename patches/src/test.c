#include "../mk64/mk64.h"
extern "C" {

extern void *currentThread;
static const char *hex = "0123456789ABCDEF";


char *strcpy_but_better(char *dest, const char *src) {
    while(*dest++ = *src++);
    return dest-1;
}

char *printHex(char *buf, u32 num, int nDigits) {
    char *bufEnd = &buf[nDigits];
    while(nDigits--) {
        buf[nDigits] = hex[num & 0xF];
        num >>= 4;
    }
    return bufEnd;
}


void init() {
    // *(u32*)0x8009F978 = 0;
    sdrv_init();
    //sdrv_dprint("hello!\n", 8);
}


void* titleHook(void *buf, int x1, int y1, int x2, int y2,
uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
    sdrv_dprint("hello!\n");
}

static int running = 0;
static volatile char text[512] __attribute__ ((aligned (16)));

void dmaThreadHook2(u32 direction, u32 devAddr, void *vAddr, u32 nBytes) {
    if(running) return;
    //if(currentThread != (void*)0x80195270) return;
    running = 1;

    //u32 intMask = __osDisableInt();
    //while(dma_busy() || sdrv_isBusy());

    u32 *t = (u32*)((u32)&text | 0xA0000000);
    //for(int i=0; i<512/4; i++) {
    //    t[i] = 0xDEADBEEF;
    //    //text[i] = (char)i;
    //}
    memset(t, 0xFFFFFFFF, 512);

    char *buf = (char*)((u32)&text | 0xA0000000);
    buf = strcpy_but_better(buf, "DMA ");
    buf = printHex(buf, devAddr, 6);
    *buf++ = ' ';
    *buf++ = direction ? '>' : '<';
    *buf++ = ' ';
    buf = printHex(buf, (u32)vAddr, 8);
    buf = strcpy_but_better(buf, " len ");
    buf = printHex(buf, nBytes, 8);
    buf = strcpy_but_better(buf, " T ");
    buf = printHex(buf, (u32)currentThread, 8);
    *buf++ = '\r';
    *buf++ = '\n';
    *buf++ = '\0';

    sdrv_dprint((char*)text);
    //evd_dprint(text, 512);
    running = 0;
    //__osRestoreInt(intMask);
}


} //extern "C"
