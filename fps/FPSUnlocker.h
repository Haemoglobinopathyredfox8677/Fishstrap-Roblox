// rev-b8f3c1-20260825 FPSUnlocker.h
#pragma once
#include <cstdint>

namespace fishstrap {

class FPSUnlocker {
public:
    void setTargetFps(int fps);   // 144 / 240 / 360 / 0 = unlimited
    bool attach(unsigned long pid);

private:
    uintptr_t findScheduler(void* proc);
    void writeDouble(void* proc, uintptr_t addr, double value);
    int targetFps_ = 240;
    int capOffset_ = 0x68;
};

} // namespace fishstrap
