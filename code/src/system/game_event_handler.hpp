#pragma once

#include <SFML/Graphics.hpp>
#include "event_handler.hpp"

class game_event_handler : public event_handler
{
public:
	game_event_handler(sf::RenderWindow& window) :
		window_(window) {}

	virtual void quit_game() override
	{
		window_.close();
	}

private:
	sf::RenderWindow& window_;
};