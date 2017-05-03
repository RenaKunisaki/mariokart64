void printTimer(int x, int y, int time); //time is probably seconds?
void* drawBox(void *buf, int x1, int y1, int x2, int y2,
    u32 r, u32 g, u32 b, u32 a);
/* draw filled box on screen. buf is where to write the display list commands.
 * returns new display list address which must be written to 0x80150298.
 * r, g, b, a are uint32_t but values are 0 to 255.
 */
