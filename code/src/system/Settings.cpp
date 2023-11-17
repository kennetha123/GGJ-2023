#include "system/Settings.h"
#include <fstream>
#include <spdlog/spdlog.h>

Settings::Settings()
{

}

SettingData Settings::loadSettings(const std::string& settings_path)
{
    SettingData data;

    auto log = spdlog::get("main");

    std::string json_file(settings_path);
    std::ifstream ifs(json_file);
    if (!ifs)
    {
        log->error("Could not open file for reading: {}", json_file);
    }

    json settings_data = json::parse(ifs, nullptr, false);
    if (settings_data.is_discarded())
    {
        log->error("Error parsing JSON data.", json_file);
    }

    data.resolution = sf::Vector2i(settings_data["resolution"][0], settings_data["resolution"][1]);
    data.is_fullscreen = settings_data["is_fullscreen"];

    return data;
}

void Settings::saveSettings(const std::string& settings_path)
{

}