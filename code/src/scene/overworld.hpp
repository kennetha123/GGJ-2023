#pragma once

#include "scene_manager.hpp"
#include "../tiled2sfml/tiled2sfml.h"
#include "character/player.h"
#include "../ui/ui_manager.hpp"
#include "system/Collision.h"

class Overworld : public scene
{
public:
	Overworld(game_context& game_context_) :
		scene(game_context_),
		main_character("../resources/Actor_sangoku01.png"),
		camera(sf::FloatRect(0, 0, 800, 600))
	{
		tiled2Sfml.setCollisionLayer({ 1, 4 });
		tiled2Sfml.tileParser("../resources/maps/", "prologue.json");
		main_character.setTilemap(tiled2Sfml);
	}

	virtual void update(float dt) override;
	virtual void draw(sf::RenderWindow& window) override;
	bool isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance);
private:
	player main_character;
	Tiled2SFML tiled2Sfml;
	sf::View camera;

	float render_distance = 550.0f;
	int player_layer = 3;
};

void Overworld::update(float dt)
{
	camera.setCenter(main_character.sprite.getPosition());
	main_character.update(dt);
}

void Overworld::draw(sf::RenderWindow& window)
{
	window.setView(camera);
	for (size_t layer_idx = 0; layer_idx < tiled2Sfml.getTilemapData().layers.size(); layer_idx++)
	{
		if (layer_idx == player_layer)
		{
			main_character.draw(window);
		}
		else
		{
			for (const auto& tile : tiled2Sfml.getTileSprite())
			{
				if (tile.layer_index == layer_idx &&
					isNearPlayer(tile.sprite.getPosition(), main_character.sprite.getPosition(), render_distance))
				{
					window.draw(tile.sprite, sf::BlendAlpha);
				}
			}
		}
	}
}

bool Overworld::isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance)
{
	float dx = tile_position.x - player_position.x;
	float dy = tile_position.y - player_position.y;
	float distance_squared = dx * dx + dy * dy;
	return distance_squared <= render_distance * render_distance;
}
