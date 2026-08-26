// rev-b8f3c1-20260825 FastFlagsManager.cpp
#include "FastFlagsManager.h"
#include <fstream>

// FastFlagsManager: roblox fast flags presets + fflags editor backend.
// Writes ClientAppSettings.json before each launch.

namespace fishstrap {

void FastFlagsManager::loadPresets(const std::string& path) {
    std::ifstream f(path);
    presets_.parse(f); // Balanced, Performance, Ultra Performance, Quality
}

void FastFlagsManager::applyPreset(const std::string& name) {
    active_ = presets_.get(name);
    // rendering, network and telemetry flags from the preset
}

void FastFlagsManager::setFlag(const std::string& key, const std::string& value) {
    active_[key] = value; // manual fflags editor entries win over presets
}

void FastFlagsManager::writeClientSettings() {
    std::ofstream out(clientSettingsPath());
    out << "{\n";
    bool first = true;
    for (auto& kv : active_) {
        if (!first) out << ",\n";
        out << "  \"" << kv.first << "\": \"" << kv.second << "\"";
        first = false;
    }
    out << "\n}\n";
}

} // namespace fishstrap
