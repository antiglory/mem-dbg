// inj.c (injection)
#pragma once

#include <stdio.h>
#include <windows.h>

#include "intf.c" // interface
#include "adi.c" // advanced input
#include "ipr.c" // is process running
#include "gpp.c" // get process permissions

#include "../def.c" // definitions

void logError(const char* message) {
    printf("[!] %s (err): %lu\n", message, GetLastError());
}

void injection(const char* dllPath) {
    input("> ", &ProcessId, 'h');

    printf("[-] starting injection at %llx\n", ProcessId);

    if (IPR(ProcessId)) {
        if (GPP(ProcessId)) {
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
            if (hProcess == NULL) {
                logError("error getting proc handle");
                return;
            }
            printf("[+] got proc handle\n");
        
            // Allocate memory for the DLL path dynamically
            dllPathSize = strlen(dllPath) + 1;
            pDllPath = VirtualAllocEx(hProcess, NULL, dllPathSize, MEM_COMMIT, PAGE_READWRITE);
            if (pDllPath == NULL) {
                logError("error allocating memory to target proc");
                freem(hProcess, NULL, NULL);
                return;
            }
            printf("[+] allocated memory to target proc\n");
        
            // Write the DLL path to the allocated memory
            if (!WriteProcessMemory(hProcess, pDllPath, dllPath, dllPathSize, NULL)) {
                logError("error writing in the proc memory");
                freem(hProcess, pDllPath, NULL);
                return;
            }
            printf("[+] wrote proc memory\n");
        
            // Get the address of the function LoadLibrary in kernel32.dll
            pLoadLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            if (pLoadLibrary == NULL) {
                logError("error getting func address");
                freem(hProcess, pDllPath, NULL);
                return;
            }
            printf("[+] got func address\n");
        
            // Create a remote thread to execute LoadLibrary with the desired DLL
            hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pDllPath, 0, NULL);
            if (hThread == NULL) {
                logError("error creating remote thread");
                freem(hProcess, pDllPath, NULL);
                return;
            }
            printf("[+] remote thread created\n");
        
            WaitForSingleObject(hThread, INFINITE);
            printf("[+] successfully injected dll\n");
        
            freem();
            program_interface();
        } else {
            logError("insufficient permissions");
        }
    } else {
        logError("process is not even running");
    }
}
