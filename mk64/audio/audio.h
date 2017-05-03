typedef enum {
    SONG_NONE = 0,
    SONG_TITLE_SCREEN,
    SONG_MENU,
    SONG_RACEWAY,
    SONG_FARM,
    SONG_CHOCO,
    SONG_BEACH,
    SONG_BOARDWALK,
    SONG_SNOW,
    SONG_BOWSER_CASTLE,
    SONG_DESERT,
    SONG_GP_START,
    SONG_FINAL_LAP,
    SONG_FIRST_PLACE,
    SONG_SECOND_PLACE,
    SONG_YOU_LOSE,
    SONG_RACE_RESULTS,
    SONG_STAR_POWER,
    SONG_RAINBOW_ROAD,
    SONG_DK_JUNGLE,
    SONG_UNKNOWN,
    SONG_TURNPIKE,
    SONG_VS_START,
    SONG_VS_RESULTS,
    SONG_RETRY_QUIT,
    SONG_BIG_DONUT,
    SONG_TROPHY1,
    SONG_TROPHY2,
    SONG_CREDITS,
    SONG_TROPHY_LOSE,
    NUM_SONGS
} SongID;

/* 803B03CB lock at 0 to disable race start sounds */
extern s8 musicSpeed;
extern s8 soundMode;

void soundPlay(int soundID);
void soundPlay2(int soundID);
