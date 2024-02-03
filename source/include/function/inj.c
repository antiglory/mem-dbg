// inj.c (injection)
#include <stdio.h>
#include <windows.h>

#include "intf.c"
#include "rdln.c"
#include "../def.c"

void injection(const char *dllPath) {
    input("> ", dwProcessId, 'w');

    // Obtenha um handle para o processo alvo
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    if (hProcess == NULL) {
        printf("[!] error getting proc handle (err): %lu\n", GetLastError());
        return;
    }

    // Aloque memória no processo alvo para o caminho da DLL
    pDllPath = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (pDllPath == NULL) {
        printf("[!] error allocating memory to target process (err): %lu\n", GetLastError());
        CloseHandle(hProcess);
        return;
    }

    // Escreva o caminho da DLL na memória alocada
    if (!WriteProcessMemory(hProcess, pDllPath, dllPath, strlen(dllPath) + 1, NULL)) {
        printf("[!] error writting in the proc memory (err): %lu\n", GetLastError());
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    // Obtenha o endereço da função LoadLibrary no kernel32.dll
    pLoadLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (pLoadLibrary == NULL) {
        printf("[!] error getting func address (err): %lu\n", GetLastError());
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    // Crie uma thread remota para executar LoadLibrary
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pDllPath, 0, NULL);
    if (hThread == NULL) {
        printf("[!] error creating remote thread (err): %lu\n", GetLastError());
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    // Aguarde a thread terminar
    WaitForSingleObject(hThread, INFINITE);
}