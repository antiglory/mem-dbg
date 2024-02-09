// adi.c (advanced input)
#pragma once

#include <stdio.h>
#include <stdlib.h>

enum DataType {
    I_INTEGER = 'd',
    I_CHAR = 'c',
    I_STRING = 's',
    I_DWORD = 'w',
    I_HEXADECIMAL = 'h'
};

void input(char* imsg, void* data, enum DataType type) {
    printf("%s", imsg);

    switch (type) {
        case I_INTEGER:
            scanf("%d", (int*)data);
            break;
        case I_CHAR:
            scanf(" %c", (char*)data);
            break;
        case I_STRING:
            scanf("%s", (char*)data);
            break;
        case I_DWORD:
            scanf("%lu", (unsigned long int*)data);
            break;
        case I_HEXADECIMAL:
            scanf("%llx", (unsigned long long int*)data);
            break;
    default:
      printf("[!] unknown data type\n");
      exit(EXIT_FAILURE);
  }
}