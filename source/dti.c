#include <windows.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

__declspec(dllexport) int memquery(HANDLE processHandle, BYTE targetValue) {
    DWORD* foundAddresses;
    int maxFound;

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    DWORD pageSize = systemInfo.dwPageSize;
    LPVOID minAddress = systemInfo.lpMinimumApplicationAddress;
    LPVOID maxAddress = systemInfo.lpMaximumApplicationAddress;

    int foundCount = 0;

    for (LPVOID currentAddress = minAddress; currentAddress < maxAddress && foundCount < maxFound; currentAddress = (LPVOID)((DWORD)currentAddress + pageSize)) {
        BYTE buffer[pageSize];
        DWORD bytesRead;

        if (ReadProcessMemory(processHandle, currentAddress, &buffer, sizeof(buffer), &bytesRead)) {
            for (DWORD i = 0; i < bytesRead; i++) {
                if (buffer[i] == targetValue) {
                    foundAddresses[foundCount++] = (DWORD)currentAddress + i;
                    if (foundCount >= maxFound) {
                        // Se atingiu o número máximo de endereços encontrados, retorna imediatamente
                        return foundCount;
                    }
                }
            }
        } else {
            return -1; // Erro ao ler a memória do processo
        }
    }

    return foundCount;
}

__declspec(dllexport) BOOL memwrite(HANDLE processHandle, DWORD address, BYTE newValue) {
    SIZE_T bytesWritten;
    return WriteProcessMemory(processHandle, (LPVOID)address, &newValue, sizeof(newValue), &bytesWritten);
}