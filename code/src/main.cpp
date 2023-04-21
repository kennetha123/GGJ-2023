#include <iostream>
#include "header.h"
#include "scene_manager.hpp"
#include "overworld.hpp"
#include "tile_manager.hpp"
#include <memory>

#include <iostream>
#include <cstdio>
#include <string>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hunters");
	sf::Clock clock;
	sf::Text fpsText;
	sf::Font font;
	font.loadFromFile("../resources/font/arial.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(0, 0);

	int frameCount = 0;
	float fpsTimer = 0;

	scene_manager mScene_manager;
	std::unique_ptr<overworld> ow = std::make_unique<overworld>();
	tile_manager tm;

	tm.tile_parser("../resources/maps/test2.txt", "world.png");
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

		// Update the FPS counter
		fpsTimer += dt.asSeconds();
		frameCount++;
		if (fpsTimer >= 1.0f)
		{
			int fps = static_cast<int>(frameCount / fpsTimer);
			fpsText.setString("FPS: " + std::to_string(fps));
			frameCount = 0;
			fpsTimer = 0;
		}
		window.clear();
		// draw tile first
		tm.render(window, ow.get()->main_character.get_component<transform_component>()->get_position(), 200.0f);
		// draw scene object
		mScene_manager.render(window);
		window.draw(fpsText);

		window.display();
	}

}