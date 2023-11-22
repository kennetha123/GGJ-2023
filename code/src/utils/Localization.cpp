#include "utils/Localization.h"
#include <fstream>
#include <iostream>
#include <codecvt>
#include <locale>

Localization::Localization(const std::string& locPath)
{
    // Read the JSON file
    std::ifstream ifs(locPath);
    if (!ifs.is_open())
    {
        std::cerr << "Could not open localization file: " << locPath << std::endl;
        return;
    }

    try
    {
        ifs >> localizationData;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return;
    }

    for (const auto& item : localizationData)
    {
        std::string id = item["ID"].get<std::string>();
        for (auto it = item.begin(); it != item.end(); ++it)
        {
            if (it.key() != "ID")
            {
                // Convert std::string (UTF-8) to std::wstring
                std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                std::wstring wide_value = converter.from_bytes(it.value().get<std::string>());

                localizations[id][it.key()] = wide_value;
            }
        }
    }
}

Localization::~Localization()
{

}

std::wstring Localization::getText(const std::string& id, const std::string& lang)
{
    if (localizations.find(id) != localizations.end() && localizations[id].find(lang) != localizations[id].end())
    {
        return localizations[id][lang];
    }
    return L"Localization ID or language not found!";
}

std::wstring Localization::convertStrtoWstr(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(str);
    return wideString;
}
