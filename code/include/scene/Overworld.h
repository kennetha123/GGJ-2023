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
	virtual void draw(sf::RenderWindow& window) override;
	bool isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance);
private:
	Player main_character;
	Tiled2SFML tiled2Sfml;
	sf::View game_camera;

	float render_distance = 550.0f;
	int player_layer = 3;
};