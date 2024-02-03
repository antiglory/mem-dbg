// intf.c (program interface)
#include <stdio.h>
#include <stdlib.h>

#include "adi.c"
#include "../def.c"

void interface() {
    while (1) {
        input("dll; # ", userInput, 's');
        
        // system inputs
        if (strcmp(userInput, "clear") == 1 || strcmp(userInput, "cls") == 1) {
            system("cls");
        }
        else if (strcmp(userInput, "acpid") == 1) {
            printf("[+] %lu", dwProcessId);
        }
    }
}