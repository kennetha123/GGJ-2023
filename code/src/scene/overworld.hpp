#include "scene_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"

class overworld : public scene
{
public:
	overworld() : 
		main_character("../resources/Actor_sangoku01.png")
	{
		tm.tile_parser("../resources/maps/world.txt", "world.png");
	}

	void update(float dt)
	{
		main_character.movement(dt);
	}

	void render(sf::RenderWindow& window)
	{
		// draw tile first
		tm.render(window, main_character.transform->get_position());

		main_character.render(window);
	}

private:
	player main_character;
	tile_manager tm;
};