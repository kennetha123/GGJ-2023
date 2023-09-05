#pragma once
#include <SFML/Graphics.hpp>

class object
{
public:
	void set_texture(sf::Texture& texture);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;
};