#define NUM_RSP_SEGMENTS       16
#define RSPSEG_FRAME_BUFFER    0x01
#define RSPSEG_COMMON_TEXTURES 0x03
#define RSPSEG_COURSE_GEOMETRY 0x04
#define RSPSEG_COURSE_TEXTURES 0x05
#define RSPSEG_COURSE_MISC     0x06 //many things here
#define RSPSEG_COURSE_DLISTS   0x07
#define RSPSEG_COURSE_TEXLIST  0x09 //texture list
#define RSPSEG_HUD_GFX         0x0D
#define RSPSEG_TEMP            0x0F //temporary buffer for decoding

extern void *rspSegmentPtr[NUM_RSP_SEGMENTS];
