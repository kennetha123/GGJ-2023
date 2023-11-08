#pragma once

#include "json.hpp"
#include <string>
#include <unordered_map>

class Localization
{
public:
	Localization(const std::string& loc_path);
	~Localization();
	std::wstring getText(const std::string& id, const std::string& lang);

private:
	nlohmann::json localizationData;
	std::unordered_map<std::string, std::unordered_map<std::string, std::wstring>> localizations;

};