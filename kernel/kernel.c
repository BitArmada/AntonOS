#include "../drivers/TextMode.h"

int main () {
    clearScreen(0x00);

    // char str[6] = {'H','E','L','L','O','\0'};

    // char str2[] = "my name is ANTON";
    // char *str3 = "this is a pointer";
    char str[] = {'H','E','L','L','O','O','O','O'};

    //printAt(str3, 0x30, 3,3);

    // printChar(str[0], 0x50, 4,5);
    // printChar(str[1], 0x50, 5,5);
    // printChar(str[2], 0x50, 6,5);
    // printChar(str[3], 0x50, 7,5);
    // printChar(str[4], 0x50, 8,5);
    // printChar(str[5], 0x50, 9,5);
    printChar('�', 0x50, 9,5);

    return 0;
}
