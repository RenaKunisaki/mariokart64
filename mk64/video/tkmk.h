typedef struct {
    char signature[6]; //"TKMK00"
    u8  offsetsUsed; //bit mask of which offsets to use
    u8  always0F;
    u16 width, height;
    u32 offsets[8];
    u8  data[];
} tkmkFile;

void tkmkDecode(const tkmkFile *in, u8 *tmpBuf, u16 *out, u16 transpColor);
