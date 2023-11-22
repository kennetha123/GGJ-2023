#pragma once

#include "character/Character.h"
#include "UI/UICONTROLLER.H"

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
	NPC::NPC(const std::string& name, const std::vector<std::string>& movement, bool is_loop,
		const sf::Vector2i& position, const std::string& dialog_path,
		const std::string& pic_path, const std::string& sprite_path);
		
	virtual void update(float dt) override;
	void setDialog(UI::Controller::DialogController* dialog);
	void interact();

	std::string _name;
	std::vector<std::string> _movement;
	std::string _dialog_path;
	std::string _pic_path;
	bool _is_loop;

private:
	void initAnimation();
	void moveRandomly();
	sf::Font font;
	std::unordered_map<std::string, sf::Vector2f> movement_direction = {
	{"right", sf::Vector2f(48.0f, 0.0f)},
	{"left", sf::Vector2f(-48.0f, 0.0f)},
	{"up", sf::Vector2f(0.0f, -48.0f)},
	{"down", sf::Vector2f(0.0f, 48.0f)}
	};

	AnimationController controller;
	UI::Controller::DialogController* dialogue_controller;
	float timer = 1.0f;
	int current_movement_index = 0;
};

class NPCManager
{
public:
	NPCManager();
	
	void setNPCScene(const std::string& json_file);
	std::shared_ptr<NPC> getNPCAtPosition(const sf::Vector2f& position);

//private:
	std::vector<std::shared_ptr<NPC>> npcs;
};