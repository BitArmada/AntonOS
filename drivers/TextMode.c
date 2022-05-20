#include "./TextMode.h"

enum Color {
    WHITE_ON_WHITE = 0xFF,
    WHITE_ON_BLACK = 0xF0
};

int getOffset(int col, int row){
    return (MAX_COLS*(row-1)+(col))*2;
}

int getCursor () {
    port_byte_out ( REG_SCREEN_CTRL , 14);
    int offset = port_byte_in ( REG_SCREEN_DATA ) << 8;
    port_byte_out ( REG_SCREEN_CTRL , 15);
    offset += port_byte_in ( REG_SCREEN_DATA );
    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset .
    return offset *2;
}

void setCursor (int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 0x0F);
	port_byte_out(REG_SCREEN_DATA, (offset & 0xFF));
	port_byte_out(REG_SCREEN_CTRL, 0x0E);
	port_byte_out(REG_SCREEN_DATA, ((offset >> 8) & 0xFF));
}
void setCursorPos (int x, int y) {
    setCursor(getOffset(x, y));
}

void printChar (char character, char attribute, int x, int y) {
    unsigned char * vidmem = ( unsigned char *) VIDEO_ADDRESS ;

    int offset = getOffset(x, y);

    vidmem[offset+1] = character;
    vidmem[offset+2] = attribute;

    setCursor(offset);
}
void printAt (char *string, char color, int x, int y) {
    unsigned char * vidmem = ( unsigned char *) VIDEO_ADDRESS ;
    int offset = getOffset(x, y);
    // int i = 0;
    // while(i < 20){//string[i+2] != 0){
    //     i++;
    //     vidmem[offset++] = (char) *(string++);
    //     vidmem[offset++] = color;
    // }
    for(int p = 0; p < 100; p++) {
        vidmem[offset++] = (char) *(string+4);
        vidmem[offset++] = color;
    }
    setCursor(offset+1);
}

void clearScreen(char color){

    for(int y = 0; y <= MAX_ROWS; y++){
        for(int x = 0; x <= MAX_COLS; x++){
            printChar(' ', color, x, y);
        }
    }

    setCursorPos(0,0);
}