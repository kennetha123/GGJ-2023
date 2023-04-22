#include "header.h"
#include "scene/scene_manager.hpp"
#include "scene/overworld.hpp"
#include "tile_manager.hpp"
#include "ui/ui_manager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hunters");

	sf::Clock clock;
	sf::Font font;
	 
	tile_manager tm;
	scene_manager scene_manager_;
	std::unique_ptr<overworld> ow = std::make_unique<overworld>();

	font.loadFromFile("../resources/font/arial.ttf");
	ui::ui_manager ui_mgr(font);

	tm.tile_parser("../resources/maps/test.txt", "world.png");
	scene_manager_.pushScene(ow.get());

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
		scene_manager_.update(dt.asSeconds());
		ui_mgr.update_fps(dt.asSeconds());

		window.clear();

		// draw tile first
		tm.render(window, ow.get()->main_character.get_component<transform_component>()->get_position(), 500.0f);

		// draw scene object
		scene_manager_.render(window);

		// draw ui
		window.draw(ui_mgr.get_fps_view().get_text());

		window.display();
	}

}