// rev-b8f3c1-20260825 Launcher.cpp
#include "../config/Config.h"
#include "../fflags/FastFlagsManager.h"
#include "../fps/FPSUnlocker.h"
#include <windows.h>
#include <tlhelp32.h>

// Launcher: detects Roblox process start (web + Microsoft Store UWP)
// and injects the FPS unlock within a second.

namespace fishstrap {

int Launcher::run() {
    DWORD lastPid = 0;
    while (true) {
        DWORD pid = findRoblox();
        if (pid && pid != lastPid) {
            fflags_.writeClientSettings(); // ClientAppSettings.json
            unlocker_.attach(pid);
            lastPid = pid;
        }
        Sleep(500);
    }
    return 0;
}

DWORD Launcher::findRoblox() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe{ sizeof(pe) };
    DWORD pid = 0;
    if (Process32First(snap, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, "RobloxPlayerBeta.exe") == 0 ||
                _stricmp(pe.szExeFile, "Windows10Universal.exe") == 0)
                pid = pe.th32ProcessID;
        } while (Process32Next(snap, &pe) && !pid);
    }
    CloseHandle(snap);
    return pid;
}

void removeInstanceLock() {
    // deletes the singleton mutex so multi instance works
    HANDLE h = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, "ROBLOX_singletonMutex");
    if (h) CloseHandle(h);
}

} // namespace fishstrap
