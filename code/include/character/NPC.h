#pragma once

#include "character/Character.h"

using json = nlohmann::json;

enum class NPCState {
	Idle,
	WalkingRight,
	Waiting,
	WalkingLeft
};

class NPC : public Character
{
public:
	NPC::NPC(const std::string& name, const std::vector<std::string>& movement,
		const sf::Vector2i& position, const std::string& dialog_path,
		const std::string& pic_path, const std::string& sprite_path);
		
	virtual void update(float dt) override;

	std::string _name;
	std::vector<std::string> _movement;
	std::string _dialog_path;
	std::string _pic_path;

private:
	AnimationController controller;

};

class NPCManager
{
public:
	NPCManager();
	
	void setNPCScene(const std::string& json_file);

//private:
	std::vector<std::shared_ptr<NPC>> npcs;
};