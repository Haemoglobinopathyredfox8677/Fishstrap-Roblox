// rev-b8f3c1-20260825 FastFlagsManager.h
#pragma once
#include <map>
#include <string>

namespace fishstrap {

struct PresetStore {
    void parse(std::istream& f);
    std::map<std::string, std::string> get(const std::string& name);
};

class FastFlagsManager {
public:
    void loadPresets(const std::string& path);
    void applyPreset(const std::string& name);
    void setFlag(const std::string& key, const std::string& value);
    void writeClientSettings();

private:
    std::string clientSettingsPath() const;
    PresetStore presets_;
    std::map<std::string, std::string> active_;
};

} // namespace fishstrap
