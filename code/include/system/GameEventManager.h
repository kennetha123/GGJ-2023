#pragma once

#include <SFML/Graphics.hpp>
#include "system/EventManager.h"

class GameEventManager : public IEvent
{
public:
	GameEventManager(sf::RenderWindow& window) :
		window_(window) {}

	virtual void quitGame() override;

private:
	sf::RenderWindow& window_;
};