// rev-b8f3c1-20260825 Config.h
#pragma once
#include <fstream>
#include <string>

namespace fishstrap {

struct Config {
    int targetFps = 240;
    bool multiInstance = false;
    bool discordRichPresence = true;
    std::string activePreset = "Balanced";
    std::string customFont;
    std::string shaderPack; // bloxshade compatible

    bool load(const std::string& path) {
        std::ifstream f(path);
        if (!f) return false;
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto eq = line.find('=');
            if (eq == std::string::npos) continue;
            auto k = line.substr(0, eq);
            auto v = line.substr(eq + 1);
            if (k == "target_fps") targetFps = std::stoi(v);
            else if (k == "multi_instance") multiInstance = (v == "1");
            else if (k == "discord_rpc") discordRichPresence = (v == "1");
            else if (k == "preset") activePreset = v;
            else if (k == "custom_font") customFont = v;
            else if (k == "shader_pack") shaderPack = v;
        }
        return true;
    }
};

} // namespace fishstrap
