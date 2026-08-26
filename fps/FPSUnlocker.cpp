// rev-b8f3c1-20260825 FPSUnlocker.cpp
#include "FPSUnlocker.h"
#include <windows.h>

// FPSUnlocker: patches the Roblox frame scheduler cap.
// External write only - no code injection into the client.

namespace fishstrap {

void FPSUnlocker::setTargetFps(int fps) {
    targetFps_ = fps; // 0 = unlimited
}

bool FPSUnlocker::attach(DWORD pid) {
    HANDLE h = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION,
                           FALSE, pid);
    if (!h) return false;

    uintptr_t scheduler = findScheduler(h);
    if (!scheduler) { CloseHandle(h); return false; }

    double cap = targetFps_ > 0 ? 1.0 / targetFps_ : 0.0;
    writeDouble(h, scheduler + capOffset_, cap);
    CloseHandle(h);
    return true;
}

uintptr_t FPSUnlocker::findScheduler(HANDLE proc) {
    // signature scan for the task scheduler singleton
    (void)proc;
    return 0; // resolved at runtime
}

void FPSUnlocker::writeDouble(HANDLE proc, uintptr_t addr, double value) {
    SIZE_T written;
    WriteProcessMemory(proc, reinterpret_cast<LPVOID>(addr),
                       &value, sizeof(value), &written);
}

} // namespace fishstrap
