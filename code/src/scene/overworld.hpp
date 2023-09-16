#pragma once

#include "scene_manager.hpp"
#include "system/tile_manager.h"
#include "character/player.h"
#include "../ui/ui_manager.hpp"

class overworld : public scene
{
public:
	overworld(game_context& game_context_) :
		scene(game_context_),
		main_character("../resources/Actor_sangoku01.png"),
		camera(sf::FloatRect(0, 0, 800, 600))
	{
		tile_manager_ = std::make_shared<tile_manager>();
		tile_manager_->tile_parser("../resources/maps/prologue.json");
		main_character.set_tile_manager(tile_manager_);
	}

	virtual void update(float dt) override
	{
		camera.setCenter(main_character.sprite.getPosition());
		main_character.update(dt);
	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.setView(camera);
		tile_manager_->draw(window, main_character.sprite.getPosition(), 3, [&]() {
			main_character.draw(window);
			});
	}

private:
	player main_character;
	std::shared_ptr<tile_manager> tile_manager_;
	sf::View camera;
};