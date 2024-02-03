#include <windows.h>

// typedefs

// prototypes
int setObj();
int setDllFuncs();

void injection(const char *dllPath);
void interface();

static int RDLN(const char* RDLN_FLN, char* RDLN_DLN);

void memwrite();
void memquery();

// main.c
char main_dllPath[256];

// intf.c
char userInput[50];

// inj.c
DWORD dwProcessId;

HANDLE hProcess;
LPVOID pDllPath;
LPVOID pLoadLibrary;
HANDLE hThread;

char dllName[256];
const char* configFileName;
int readDllName_handler;

// dll funcs


// funcs
int setObj() {
    main_dllPath = "dti.dll";
    // [...]
    return 1;
}

int setDllFuncs() {
    // [...]
    return 1;
}

int freem() {
    if (CloseHandle(hThread)) {
        if (VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE)) {
            CloseHandle(hProcess);

            return 1;
        }
    }
}