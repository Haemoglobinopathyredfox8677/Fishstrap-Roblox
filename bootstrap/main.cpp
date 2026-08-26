// rev-b8f3c1-20260825 main.cpp
#include "../config/Config.h"
#include "../fflags/FastFlagsManager.h"
#include "../fps/FPSUnlocker.h"
#include <iostream>

// Fishstrap - roblox bootstrapper with fps unlocker and fast flags.
// Watches for Roblox launches and applies settings automatically.

int main(int argc, char** argv) {
    fishstrap::Config cfg;
    cfg.load("bundle/settings.cfg");

    fishstrap::FastFlagsManager fflags;
    fflags.loadPresets("bundle/presets.json");
    if (!cfg.activePreset.empty())
        fflags.applyPreset(cfg.activePreset); // Balanced / Performance / Ultra

    fishstrap::FPSUnlocker unlocker;
    unlocker.setTargetFps(cfg.targetFps); // 144, 240, 360, unlimited

    if (cfg.multiInstance)
        fishstrap::removeInstanceLock(); // run several roblox clients

    std::cout << "Fishstrap v2.9.0 - watching for Roblox...\n";
    fishstrap::Launcher watcher(cfg, fflags, unlocker);
    return watcher.run(); // unlock applies on every game launch
}
