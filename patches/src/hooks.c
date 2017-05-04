#include "main.h"
extern "C" {


void hooks_init() {
    //Called at boot once our code is loaded into RAM.
    sdrv_init();
}


//void* titleHook(void *buf, int x1, int y1, int x2, int y2,
//uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
//    sdrv_dprint("hello!\n");
//}


void dmaThreadHook(u32 direction, u32 devAddr, void *vAddr, u32 nBytes) {
    //Called by the PI thread when a DMA is about to begin.

    //if(currentThread != (void*)0x80195270) return;

    //log this DMA to debug print
    char text[512] __attribute__ ((aligned (16)));
    char *buf = text;
    buf = strAppend(buf, "DMA ");
    buf = printHex (buf, devAddr, 6);
    *buf++ = ' ';
    *buf++ = direction ? '>' : '<';
    *buf++ = ' ';
    buf = printHex (buf, (u32)vAddr, 8);
    buf = strAppend(buf, " len ");
    buf = printHex (buf, nBytes, 8);
    buf = strAppend(buf, " T ");
    buf = printHex (buf, (u32)currentThread, 8);
    *buf++ = '\r';
    *buf++ = '\n';
    *buf++ = '\0';
    sdrv_dprint(text);
}

} //extern "C"
