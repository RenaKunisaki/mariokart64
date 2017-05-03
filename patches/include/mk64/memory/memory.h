void dmaCopy(void *dest, const void *src, unsigned int size);
//void bcopy(const void *src, void *dst, int size);
void mio0Decode(const void *src, void *dst);
uint32_t mio0Encode(const void *src, u32 length, void *dst); //returns compressed size

extern void *heapEndPtr, *heapEnd;

/* To make the heap occupy the Expansion Pak region,
 * change the following ROM addresses:
 *   0x113FBA = 0x8080 (normally 0x8028)
 *   0x113FCE = 0x00   (normally 0xDF)
 */
