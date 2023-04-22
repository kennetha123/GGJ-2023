#pragma once

#include <SFML/Graphics.hpp>
#include "scene_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"

class overworld : public scene
{
public:
	overworld() : 
		main_character("../resources/Actor_sangoku01.png"),
		camera(sf::FloatRect(0, 0, 800, 600))
	{
		tm.tile_parser("../resources/maps/test1.txt", "world.png");
	}

	void update(float dt)
	{
		camera.setCenter(main_character.transform->get_position());
		main_character.movement(dt);
	}

	void draw(sf::RenderWindow& window)
	{
		window.setView(camera);
		
		tm.draw(window, main_character.transform->get_position(), 0);
		main_character.draw(window);
		tm.draw(window, main_character.transform->get_position(), 1);
	}

private:
	player main_character;
	tile_manager tm;

	sf::View camera;

};