#pragma once
#include <SFML/Graphics.hpp>

class object
{
public:
	void load_image(const std::string& image_path)
	{
		if (!texture.loadFromFile(image_path))
		{
			printf_s("Failed to load file!");
		}

		sprite.setTexture(texture);
		sprite.setOrigin(-400, -300);
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	sf::Sprite sprite;
	sf::Texture texture;
};