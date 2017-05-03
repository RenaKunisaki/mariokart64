//in-game colorful text
typedef enum {
    TEXT_BLUE = 0,
    TEXT_GREEN,
    TEXT_RED,
    TEXT_YELLOW,
    TEXT_TRANS1, //color transition effects
    TEXT_TRANS2
} TextColor;

void textSetColor(int col);
void textDrawPtr(int *x, int *y, const char *str, int spacing,
    float xScale, float yScale);
void textDraw(int x, int y, const char *str, int spacing,
    float xScale, float yScale);

/** textDrawPtr() takes pointers to the coordinate variables and updates
 *  them to the coordinates of the next character after the string.
 *  xScale and yScale are used to stretch the text.
 *  spacing is how many pixels between letters.
 */

/* 800E86F4 "01", "NKTJ", debug text */

extern char coordDisplayText[28]; //"SOUTH EAST NORTH WEST SOUTH"
/* 800EC121 some text relating to generating AI path source code */
/* 800EF868 some text */
extern char replayText[7]; //"REPLAY"
