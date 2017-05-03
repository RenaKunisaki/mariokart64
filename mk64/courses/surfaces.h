typedef enum {
    SURFACE_PAVEMENT = 1,
    SURFACE_DIRT_TRACK, //edge of pools, dirt track
    SURFACE_SAND_OOB, //out of bounds beach sand
    SURFACE_CONCRETE,
    SURFACE_SNOW_TRACK,
    SURFACE_WOOD,
    SURFACE_DIRT,
    SURFACE_GRASS,
    SURFACE_ICE_TRACK,
    SURFACE_SAND,
    SURFACE_SNOW_OOB,
    SURFACE_ROCK_WALL,
    SURFACE_DIRT_OFF_TRACK,
    SURFACE_TRAIN_TRACKS,
    SURFACE_INSIDE_CAVE,
    SURFACE_ROPE_BRIDGE,
    SURFACE_DK_BOOST_RAMP = -4,
    SURFACE_OUT_OF_BOUNDS = -3,
    SURFACE_ROYAL_BOOST_RAMP = -2,
    SURFACE_SOLID = -1,
} SurfaceType;

//surface map flags
#define SMAP_FLAG_15 0x8000 //unknown purpose
#define SMAP_SOLID_FROM_BEHIND 0x4000 //polygons are solid from both sides
#define SMAP_FLAG_13 0x2000 //unknown purpose

typedef struct {
	rspPtr   dlist;      //display list to parse
	u8  type;       //surface type
	u8  area;       //area ID to render
	u16 flags;
} romSurfaceMap;

typedef struct {
	u8  flags; //byte 0x00
		//bit 7: 1 = only tangible if landed on, not if driven onto?
		//       very weird. game crashes sometimes when playing with this.
		//bit 6: 1 = Lakitu can drop you here (XXX verify)
		//bit 4: 1 = out of bounds
		//bit 3: 1 = player tumbles upon contact (may fall right through)
	u8  area;
	u8  alt_type; //byte 0x02
		//usually 0. Code at 0x802AFF84 copies this value to 0x800F6B4C, which
		//stores the surface type player 1 is currently on (0 meaning none, i.e.
		//airborne).
	u8  type;
	vec3i    vtx3; //X, Y, Z of poly's third vertex
	vec3i    vtx2; //X, Y, Z of poly's second vertex
	s16* vtxs[3]; //pointer to the 3 vertices of this poly
		//unsure why this exists along with a copy of two of the vertices.
		//both are involved in hit detection.
	float    height;
		//normally 0; read at 0x802AB1A4. this value is added to the height Lakitu
		//drops you at. changing it seems to make the surface intangible.
	float    gravity;
		//normally 1. The height Lakitu drops you off at is divided by this value
		//(before adding the value at 0x1C), although if set to zero, he just tries
		//to drop you at about the height of the finish line banner. Changing it
		//has various unusual effects, making the polygon intangible or
		//significantly reducing the gravity above it, probably depending on its Y
		//position.
	float    rotation; //normally about -0.001. no idea what this actually is.
	float    height2; //changes Y position of all vertices (but not graphics or
		//Lakitu drop position). Normally set to (track_height * -1) + about 6.
} ramSurfaceMap;

void loadSurfaceMap(); //0x80290DAC - XXX params
//0x802B94A4 sets surface map offsets
