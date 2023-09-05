#include "system/object.h"

	void object::set_texture(sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	}

	void object::draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}