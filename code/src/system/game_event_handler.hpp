#pragma once

#include <SFML/Graphics.hpp>
#include "event_handler.hpp"

class GameEventManager : public IEvent
{
public:
	GameEventManager(sf::RenderWindow& window) :
		window_(window) {}

	virtual void quitGame() override
	{
		window_.close();
	}

private:
	sf::RenderWindow& window_;
};