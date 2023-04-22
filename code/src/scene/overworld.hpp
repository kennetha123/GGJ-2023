#include "scene_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"

class overworld : public scene
{
public:
	overworld() : 
		main_character("../resources/Actor_sangoku01.png")
	{
	
	}

	void update(float dt)
	{
		main_character.movement(dt);
	}

	void render(sf::RenderWindow& window)
	{
		main_character.render(window);
	}


	player main_character;
};