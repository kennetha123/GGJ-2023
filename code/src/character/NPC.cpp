#include "character/NPC.h"
#include "json.hpp"

NPC::NPC(const std::string& name,
    const std::vector<std::string>& movement,
    const sf::Vector2i& position,
    const std::string& dialog_path,
    const std::string& pic_path,
    const std::string& sprite_path) :
	Character(sprite_path, sf::Vector2i(48, 48)),
    _name(name),
    _movement(movement),
    _dialog_path(dialog_path),
    _pic_path(pic_path)
{
    sprite.setPosition(sf::Vector2f(position.x, position.y));
}

void NPC::update(float dt)
{
    Character::update(dt);
}

NPCManager::NPCManager()
{

}

void NPCManager::setNPCScene(const std::string& json_file)
{
    auto log = spdlog::get("main");

    std::ifstream ifs(json_file);
    if (!ifs)
    {
        log->error("Could not open file for reading: {}", json_file);
        return;
    }
    
    json npc_data = json::parse(ifs, nullptr, false);
    if (npc_data.is_discarded())
    {
        log->error("Error parsing JSON data.", json_file);
        return;
    }

    for (const auto& item : npc_data)
    {
        sf::Vector2i pos(item["position"][0], item["position"][1]);
        auto npc = std::make_shared<NPC>(
            item["name"],
            item["movement"].get<std::vector<std::string>>(),
            pos,
            item["dialogue"],
            item["picture"],
            item["sprite"]
        );

        npcs.push_back(npc);
    }
}