#include <windows.h>

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
DWORD dwProcessId;

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
    if (CloseHandle(hThread)) {
        if (VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE)) {
            if (CloseHandle(hProcess)) {
                return 1;
            }
        }
    } else {
        return 0;
    }
}