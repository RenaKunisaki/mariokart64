extern struct {
    struct { u16 r, g, b; } top, bottom; //why uint16_t? no idea.
    //upper bytes seem to be used for something...
} skyColor[NUM_COURSES];

extern s16 curDisplayList1; //XXX size, players
extern s16 curDisplayList2; //copied here
extern float viewPort; //XXX details

extern s16 blackSkyOnSomeCoursesIfZero; //XXX what is this?

/* 800DDEB0 array of 16bit wheel sizes */
