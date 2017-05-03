//this is added to rom_offset in textureList for some reason
extern u32 textureListRomOffset;

//800115F4 process path data
//8029D584 place something in segment 6
//8029D60C place Bowser Castle bushes in segment 6
//8029D830 place item boxes in segment 6
//802A7B94 segment base setter
//802A9AF4 unpack dlist
//802AA918 main course load routines
//802B8D80 course data ref table, or level header
//802B9C94 Jump table for segment 7 display list unpacking
//802BA274 Index for packed dlist commands

typedef struct {
	u32 seg6_addr;      //(0x00) ROM address at which segment 6 file begins
	u32 seg6_end;       //(0x04) ROM address at which segment 6 file ends
	u32 seg4_addr;      //(0x08) ROM address at which segment 4 file begins
	u32 seg7_end;       //(0x0C) ROM address at which segment 7 (not 4) file ends
	u32 seg9_addr;      //(0x10) ROM address at which segment 9 file begins
	u32 seg9_end;       //(0x14) ROM address at which segment 9 file ends
	u32 seg47_buf;      //(0x18) RSP address of compressed segments 4 and 7
	u32 numVtxs;        //(0x1C) number of vertices in the vertex file
	u32 seg7_ptr;       //(0x20) RSP address at which segment 7 data begins
	u32 seg7_size;      //(0x24) Size of segment 7 data after decompression, minus 8 bytes for some reason
	u32 texture_addr;   //(0x28) RSP address of texture list
	u16 flag;           //(0x2C) Unknown
	u16 unused;         //(0x2E) Padding
} trackHeader;
//headers begin at 0x122390 in US ROM

typedef struct { //track vertex data in ROM
    s16  X, Y, Z, S, T;
    u8  R, G, B, A;
} romVertex;

typedef struct { //track vertex data in RAM
    s16  X, Y, Z, S, T;
    u8 unk0, unk1;
    u8  R, G, B, A;
} ramVertex;

typedef struct {
	u32 rom_offset; //ROM offset of texture file (-textureListRomOffset)
	u32 file_size;  //size of compressed file
	u32 data_size;  //size of uncompressed image data
	u32 padding;    //always zero
} textureList;
