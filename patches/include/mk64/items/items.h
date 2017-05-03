typedef enum {
    ITEM_NONE = 0,
    ITEM_BANANA,
    ITEM_TRIPLE_BANANA,
    ITEM_GREEN_SHELL,
    ITEM_TRIPLE_GREEN_SHELL,
    ITEM_RED_SHELL,
    ITEM_TRIPLE_RED_SHELL,
    ITEM_BLUE_SHELL,
    ITEM_LIGHTNING,
    ITEM_FAKE_ITEM,
    ITEM_STAR,
    ITEM_GHOST,
    ITEM_1SHROOM,
    ITEM_2SHROOM,
    ITEM_3SHROOM,
    ITEM_GOLD_SHROOM,
    NUM_ITEMS
} ItemID;

/* Item probability tables:
801A7A90  8 entries - GP, human
801A7DB0  8 entries - GP, CPU
801A80D0  2 entries - VS 2P
801A8198  3 entries - VS 3P
801A82C4  4 entries - VS 4P
801A8454  1 entry   - battle mode
The probability tables work like this: Each race position has 1 entry. Each entry has 100 cells. Each cell has a weapon value in it. A cell is chosen at random when we hit an item box in the given position.
*/

int genRandomItem(int place, int playerType);
    //place: race position
    //playerType: 0=human, 1=CPU
    //returns random item ID
void* doItemLookup(int offset); //returns "pointer to item table"
//802B2FEC item pointer table:
//802B301C - 1 Banana
//802B302C - Multi Banana
//802B2FEC - 1 Green Shell
//802B30BC - 3 Green Shells
//802B2FFC - 1 Red Shell
//802B30CC - 3 Red Shells
//802B300C - Blue Shell
//802B309C - Lightning Bolt
//802B30AC - Fake Item Box (Bomb)
//802B308C - Star
//802B307C - Ghost
//802B303C - 1 Mushroom
//802B304C - 2 Mushrooms
//802B305C - 3 Mushrooms
//802B306C - Gold Mushroom

extern u8 player1_item; //XXX probably int16_t
extern s8 player1_itemControl; //1=get random item
