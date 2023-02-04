#include <iostream>
#include "header.h"
#include "scene_manager.hpp"
#include "overworld.hpp"
#include "tile_manager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hunters");
	sf::Clock clock;
	scene_manager mScene_manager;
	overworld* ow = new overworld();
	tile_manager tm;

	mScene_manager.pushScene(ow);
	tm.generate_tiles();

	while (window.isOpen())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Time dt = clock.restart();
		mScene_manager.update(dt);

		window.clear();
		
		mScene_manager.render(window);
		tm.render(window);

		window.display();
	}

}