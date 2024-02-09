// gpp.c (get process permissions)
#pragma once

#include <windows.h>
#include <stdio.h>

BOOL GPP(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processId);

    if (hProcess != NULL) {
        CloseHandle(hProcess);
        return TRUE;
    } else {
        return FALSE;
    }
}