// rdln.c (read dll name)
#pragma once

#include <stdio.h>
#include <string.h>

#include "../def.c" // definitions

static int RDLN(const char* RDLN_FLN, char* RDLN_DLN) {
  FILE* file = fopen(RDLN_FLN, "r");
  if (file != NULL) {
    // launching dll name to evade trash memory
    RDLN_DLN[0] = '\0';

    while (fgets(readDllName_line, sizeof(readDllName_line), file) != NULL) {
      // search for DLL_NAME readDllName_line
      if (strstr(readDllName_line, "DLL_NAME") != NULL) {
        // found the target readDllName_line, and extracts readDllName_line readDllName_value
        readDllName_value = strchr(readDllName_line, '=');
        if (readDllName_value != NULL) {
          readDllName_value++; // go to the next character after =
          // remove blank spaces at the start of the string
          while (isspace((unsigned char)*readDllName_value)) {
            readDllName_value++;
          }
          // copy readDllName_value to RDLN_DLN
          strcpy(RDLN_DLN, readDllName_value);
          // remove blank spaces at the end of the string
          readDllName_len = strlen(RDLN_DLN); 
          while (readDllName_len > 0 && isspace((unsigned char)RDLN_DLN[readDllName_len - 1])) {
            RDLN_DLN[--readDllName_len] = '\0';
          }
          fclose(file);
          return 0; // sucess
        }
      }
    }

    fclose(file);
    return 1; // error reading (cannot find DLL_NAME on .ini)
  }
  else {
    return 1; // error launching ini
  }
}