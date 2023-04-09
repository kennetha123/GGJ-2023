#include <iostream>
#include "header.h"
#include "scene_manager.hpp"
#include "overworld.hpp"
#include "tile_manager.hpp"
#include <memory>
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hunters");
	sf::Clock clock;
	scene_manager mScene_manager;
	std::unique_ptr<overworld> ow = std::make_unique<overworld>();
	tile_manager tm;

	tm.generate_tiles();
	mScene_manager.pushScene(ow.get());

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
		mScene_manager.update(dt.asSeconds());

		window.clear();
		
		// draw tile first
		tm.render(window);
		// draw scene object
		mScene_manager.render(window);

		window.display();
	}

}