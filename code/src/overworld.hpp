#include "scene_manager.hpp"
#include "tile_manager.hpp"
#include "player.hpp"

class overworld : public scene
{
public:
	overworld() : 
		main_character("../resources/test_player.png")
	{
	
	}

	void update(sf::Time dt)
	{
		main_character.movement();
	}

	void render(sf::RenderWindow& window)
	{
		main_character.render(window);
	}

private:
	player main_character;
};