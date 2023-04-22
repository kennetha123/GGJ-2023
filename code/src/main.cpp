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
	std::shared_ptr<overworld> ow = std::make_shared<overworld>();

	font.loadFromFile("../resources/font/arial.ttf");
	ui::ui_manager ui_mgr;
	std::shared_ptr<ui::controller::fps_controller> fps_view = std::make_shared<ui::controller::fps_controller>(font);

	tm.tile_parser("../resources/maps/test.txt", "world.png");

	scene_manager_.pushScene(std::dynamic_pointer_cast<scene>(ow));
	ui_mgr.push(fps_view);

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
		ui_mgr.update(dt.asSeconds());

		window.clear();

		// draw tile first
		tm.render(window, ow.get()->main_character.get_component<transform_component>()->get_position(), 500.0f);

		// draw scene object
		scene_manager_.render(window);

		// draw ui
		ui_mgr.draw(window);

		window.display();
	}

}