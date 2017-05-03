#ifndef _N64_MIO0_H_
#define _N64_MIO0_H_

typedef struct {
    char signature[4];   //"MIO0"
    u32  rawSize;    //Size of decompressed data
    u32  compOffs;   //Offset of compressed data
    u32  rawOffs;    //Offset of uncompressed data
    u8   data[];     //compressed data
} mio0File;

#endif //_N64_MIO0_H_
