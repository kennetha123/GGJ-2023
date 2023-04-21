#pragma once
#include <SFML/Graphics.hpp>

class object
{
public:
	void set_texture(sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	}

	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	sf::Sprite sprite;
};