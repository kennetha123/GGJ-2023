#pragma once

#include <SFML/Graphics.hpp>
#include "scene_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"
#include "../ui/ui_manager.hpp"

class overworld : public scene
{
public:
	overworld(ui::ui_manager& ui_mgr) : 
		main_character("../resources/Actor_sangoku01.png"),
		camera(sf::FloatRect(0, 0, 800, 600))
	{
		tm.tile_parser("../resources/maps/test.txt", "world.png");
	}

	virtual void update(float dt) override
	{
		camera.setCenter(main_character.sprite.getPosition());
		main_character.movement(dt);
	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.setView(camera);
		
		tm.draw(window, main_character.sprite.getPosition(), 0);
		main_character.draw(window);
		tm.draw(window, main_character.sprite.getPosition(), 1);
	}

private:
	player main_character;
	tile_manager tm;
	sf::View camera;

};