// ipr.c (is process running)
#include <windows.h>

// definitions
HANDLE hProcessSnap;
PROCESSENTRY32 pe32;

BOOL isProcessRunning(DWORD processId) {
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    return FALSE;
  }

  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (!Process32First(hProcessSnap, &pe32)) {
    CloseHandle(hProcessSnap);
    return FALSE;
  }

  do {
    if (pe32.th32ProcessID == processId) {
      CloseHandle(hProcessSnap);
      return TRUE;
    }
  } while (Process32Next(hProcessSnap, &pe32));

  CloseHandle(hProcessSnap);
  return FALSE;
}