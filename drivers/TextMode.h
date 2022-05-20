#include "../kernel/LowLevel.h"
#include "../kernel/Util.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

enum Color;

int getCursor ();
void setCursor (int offset);
void setCursorPos (int x, int y);

int getOffset(int col, int row);

void printChar (char character, char attribute, int col, int row);

void printAt (char *str, char attribute, int col, int row);

void clearScreen (char color);