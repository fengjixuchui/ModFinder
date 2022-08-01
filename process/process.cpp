#include "process.hpp"

HANDLE process::get_handle_by_name(PCSTR proc) {
    DWORD pid = 0;

    // Create toolhelp snapshot
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Enumerate processes
    if (Process32First(snapshot, &process)) {
        do {
            // Compare process exe with our string.
            // If returned true, set pid to the current process.
            if (!strcmp(process.szExeFile, proc)) {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    // Cleanup.
    CloseHandle(snapshot);

    if (pid)
        return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    // Not found.
    return NULL;
}