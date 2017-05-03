void debugLoadFont(); //actually probably sets up rendering or something
void debugPrintStrPtr(int *x, int *y, const char *str);
void debugPrintStr(int x, int y, const char *str);

/** debugPrintStrPtr() takes pointers to the coordinate variables and updates
 *  them to the coordinates of the next character after the string.
 */

void debugPrintNumber(int *x, int *y, int num, int base);
/** prints signed integer in specified base
 *  0x80057554 write 0x1000 to make it unsigned (patch the code)
 */

void debugPrintStrNum(int x, int y, const char *str, int num);
/** prints specified string followed by specified number (base 10, signed) */

extern  s8  debugMenuCursorPos;
extern  s16 debugCoordDisplay; //1=on, requires debug mode
extern  s16 debugResourceMeters; //1=on, requires debug mode
extern u16 crashScreenCodeButtons[10];
extern  s16 crashScreenCodeEntryCounter;

extern u8  debugFontMap[]; //array of ASCII -> debug font char index
//XXX size

extern u16 debugNumberSignCheck;

//0x80001620 is part of the routine that draws the coord display
//0x80001760 is part of frame advance
//0x80290008 is pressing Z to start race early
//0x8028FB28 is presing d-pad to skip laps
