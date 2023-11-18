#pragma once
#include <json.hpp>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

struct SettingData
{
public:
	sf::Vector2i resolution;
	bool is_fullscreen;
};

class Settings
{
public:
	Settings();

	SettingData loadSettings(const std::string& settings_path);
	void saveSettings(const std::string& settings_path);
};