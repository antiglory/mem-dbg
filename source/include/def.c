// def.c (definitions and etc)
#pragma once

#include <windows.h> // winapi

// typedefs

// prototypes
void injection(const char *dllPath);

int setObj();
int freem();

// main.c -------------------------
char main_dllPath[256];

// intf.c --------------------------
char userInput[50];

// inj.c  --------------------------
DWORD ProcessId;

size_t dllPathSize;

HANDLE hProcess;
HANDLE hThread;

LPVOID pDllPath;
LPVOID pLoadLibrary;

char dllName[256];
const char* configFileName;

int readDllName_handler;

// rdln.c  ------------------------
char readDllName_line[256];
char* readDllName_value;

size_t readDllName_len;

// funcs
int setObj() {
    if (memset(dllName, 0, sizeof(dllName))) {
        if (configFileName = "config.ini") {
            return 1;
        }
    } else {
        return 0;
    }
}

int freem() {
    int sucess;
    if (hThread != NULL) {
        CloseHandle(hThread);
        sucess = 1;
    }
    if (pDllPath != NULL) {
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        sucess = 2;
    }
    if (hProcess != NULL) {
        CloseHandle(hProcess);
        sucess = 3;
    }
    if (sucess == 3) {
        return 0;
    } else {
        return 1;
    }
}