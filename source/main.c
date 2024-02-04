#include <windows.h> // winapi
#include <stdio.h>
#include <stdlib.h>

#include "include/def.c" // definitions of objects

#include "include/function/rdln.c"
#include "include/function/adi.c"

int main(int argc, char const* argv[]) {
    if (setObj() == 0) {
        printf("[!] fatal error ocurred\n");
        getchar();
        return 1;
    }

    readDllName_handler = RDLN(configFileName, main_dllPath);
    if (readDllName_handler == 1) {
        printf("[!] cant read dll name\n");
        return 0;
    }

    injection(main_dllPath);
}