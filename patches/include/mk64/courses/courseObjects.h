#define MAX_ITEMS_ON_COURSE 100
extern s8 numItemsOnCourse;

//XXX verify return types
//these take a pointer to the object data in an RSP segment.
//they're called when loading a track.
void loadItemBoxes(rspPtr src);
void loadTrees(rspPtr src);
void loadPiranhaPlants(rspPtr src);
void loadPalmTrees(rspPtr src);
void loadFallingRocks(rspPtr src);

//XXX verify types.
//buf is SP + x40
void loadGiantEgg(void *buf, float X, float Y, float Z);

//called from 0x8029E380 in Luigi Raceway
//params: 0x0F035568, 0x0400, 0x0800
void loadSomeCourseObject(rspPtr a0, int a1, int a2);


typedef struct {
    s16 type;     // 00: used in switch at 802A3568
    s16 flags;    // 02: non-zero if used, 0x800 = gone (tree hit by star)
    s16 i16_04;   // 04: 1 = visible, -1 = not visible, used as timer in KD RR crossing
    s16 i16_06;   // 06: TODO some sort of state: 3 = touched by kart?
    s16 i16_08;   // 08: TODO, also float in proc_8029817C(), proc_802A10F0(), proc_802B0E98()
    s16 i16_0A;   // 0A: TODO
    float   f32_0C; // 0C: float in fake item box
    vec3i   rotation;
    s16 unk_16; //rotation quaternion?
    vec3f   position;
    union {
        struct {
            float f32_24; // 24: TODO
            float f32_28; // 28: TODO fake item box
        } item_box;
        struct {
            s16 i16_24;   // 24: TODO: state in piranha plant?
            s16 i16_26;   // 26: TODO: state in piranha plant?
            s16 i16_28;   // 28: TODO: state in piranha plant?
            s16 i16_2A;   // 2A: TODO
        } piranha;
        struct {
            float f32_24; // 24: TODO
            float f32_28; // 28: TODO
            float f32_2C; // 2C: TODO
        } triple_shell;
        struct {
            float f32_24; // 24
            float f32_28; // 28
            float f32_2C; // 2C
            // 30,34,38?
            float f32_3C; // 3C
            float f32_40; // 40
            float f32_44; // 44
            float f32_48; // 48
            float f32_4C; // 4C
            float f32_50; // 50
            float f32_54; // 54
            float f32_58; // 58
            float f32_5C; // 5C
            float f32_60; // 60
            float f32_64; // 64
            // 68,6C?
        } rocks;
    };
    // ?-6F
} SimpleObject;
extern SimpleObject simpleObjects[MAX_ITEMS_ON_COURSE];

typedef struct {
    int   unk_00;
    int   unk_04;
    float shadow_ypos;
    int   unk_0C;
    int   unk_10;
    int   unk_14;
    int   unk_18;
    vec3f position;
    //XXX more?
} ItemBox;
//extern ItemBox itemBoxes[?]; //XXX how many?


typedef struct { //size: 0xE0 bytes
    float    scale;
    vec3f    position, basePosition;
    float    f32_1C; // start of structure passed through A1 to proc_80042A20
    float    f32_20;
    float    f32_24;
    vec3f    deltaPosition; //used in proc_80050E34
    float    f32_34;
    float    f32_38; // proc_80054E10
    float    f32_3C; // proc_80054E10, proc_80074924
    float    f32_40; // proc_80054E10
    float    f32_44; // proc_80054E10, proc_8004A6EC, proc_80055CCC, proc_800568A0
     s32 i32_48; // proc_80073E18
     s32 i32_4C; // init to -1 in proc_8006EE7C, used in proc_8007375C
    u32 u32_50; // proc_8007278C
    u32 u32_54;
    u32 u32_58;
    u32 u32_5C;
     s32 i32_60; // init to -0x2128 in proc_8006EE7C
     s32 i32_64; // init to  -0x128 in proc_8006EE7C
     s32 i32_68; // init to -0x2128 in proc_8006EE7C
     s32 i32_6C; // init to  -0x128 in proc_8006EE7C
    u32 u32_70; // proc_80055164
    u32 u32_74; // proc_800518F8, proc_800519D4, proc_80055164
    u32 unk_78; // 78
    u32 unk_7C; // 7C
    u32 unk_80; // 80
     s16 i16_84; // proc_80053D74, proc_80054AFC, proc_80074924
     s16 i16_86; // proc_80053D74, proc_80054AFC, proc_80074924
     s16 i16_88; // proc_80053D74, proc_80054AFC, proc_80074924
     s16 i16_8A; // proc_80053D74, proc_80074924
     s16 i16_8C; // proc_80053D74, proc_80074924
     s16 i16_8E; // proc_80053D74, proc_80074924
     s16 i16_90; // proc_80053D74, proc_80074924
     s16 i16_92; // proc_800528EC, proc_80074924
    u16 u16_94; // proc_80085878, proc_80088364, proc_8008B284, proc_8008B620, proc_8008B6A4
     s16 i16_96; // proc_80088364, proc_8008B284, proc_8008B620, proc_8008B6A4
    u16 u16_98; // proc_8007AC9C, proc_8008B478, proc_8008B620, proc_8008B6A4
    // 9A
     s16 i16_9C; // casts f32_04 to u16 in proc_8008BFC0, read in proc_80051ABC, proc_80051C60
     s16 i16_9E; // casts f32_08 to u16 in proc_8008BFC0, read in proc_80051ABC, proc_80051C60
     s16 i16_A0; // opacity? starts at 0xFF and decays to 0x00
     s16 i16_A2; // proc_80054324, proc_80055164
     s16 i16_A4;
     s16 i16_A6; // proc_80074E28, proc_80074EE8, proc_80075CA8
     s16 i16_A8;
     s16 i16_AA; // proc_8007401C
     s16 i16_AC; // proc_800738A8, proc_80073A10
     s16 i16_AE; // proc_8008BFFC, proc_80074D94
     s16 i16_B0; // proc_8007FB48, proc_8007FB48, proc_80087060
    u16 u16_B2; // start of structure passed through A1 to proc_800484BC
    u16 u16_B4;
    u16 u16_B6;
    u16 u16_B8; // start of structure passed through A1 to proc_80042E00
    u16 u16_BA;
    u16 u16_BC;
    u16 u16_BE; // start of structure passed through A1 to proc_80042E00
    u16 u16_C0; // proc_80055CCC, proc_80070250
    u16 u16_C2; // proc_80055CCC, proc_8005A14C
    u32 unk_C4; // C4
    u32 unk_C8; // C8
    u8  u08_CA; // is used flag?
    u8  u08_CB; // proc_8007278C, proc_80072B48
     s8  i08_CC; // proc_80072C00
     s8  i08_CD; // proc_8007401C
     s8  i08_CE; // proc_8007401C
    u8  u08_CF;
     s8  i08_D0; // proc_800738A8, proc_80073A10
     s8  i08_D1; // proc_8007CC00, proc_8007FB48
     s8  i08_D2; // proc_800557B4, proc_800747F0
     s8  i08_D3; // proc_80073404, proc_8007466C, proc_800747F0
     s8  i08_D4; // proc_80072C00
    u8  u08_D5; // proc_800750D8, proc_80075698
    u8  u08_D6; // proc_80073600, proc_80073654
    u8  u08_D7; // proc_800724F8
    u8  u08_D8; // proc_800557B4, proc_800723A4
    u8  u08_D9; // proc_800518F8, proc_800519D4
    u8  u08_DA; // proc_800518F8, proc_800519D4
    u8  u08_DB; // proc_80073FAC
    u8  u08_DC; // proc_8007381C
    u8  u08_DD; // proc_8008275C, proc_800850B0
    u8  u08_DE; // proc_8008BFFC
    u8  i08_DF; // proc_80053870
} CourseObject;
extern CourseObject courseObjects[550]; //XXX really so many?
