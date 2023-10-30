#pragma once

#include "../tiled2sfml/tiled2sfml.h"
#include "scene/SceneManager.h"
#include "character/player.h"
#include "UI/UiManager.h"
#include "system/Collision.h"

class Overworld : public Scene
{
public:
	Overworld();
	virtual void update(float dt) override;
private:
	Player main_character;
	Tiled2SFML tiled2Sfml;
	sf::View game_camera;
	sf::Font font;

	float render_distance = 550.0f;
	int player_layer = 3;
	RenderManager& render;
};