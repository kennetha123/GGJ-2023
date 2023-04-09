#pragma once
#include "object.hpp"

class player : public object
{
public:
	player(const std::string& image_path) 
	{
		if (!player_texture.loadFromFile(image_path))
		{
			printf_s("Failed to load file!");
		}

		set_texture(player_texture);
		sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));

	}

	~player() = default;

	void movement(float dt)
	{
		sf::Vector2f dest;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sprite.move(-0.1f * dt * speed, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 48, sprite_width, sprite_height));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sprite.move(0.0f, -0.1f * dt * speed);
			sprite.setTextureRect(sf::IntRect(0, 144, sprite_width, sprite_height));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sprite.move(0.0f, 0.1f * dt * speed);
			sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sprite.move(0.1f * dt * speed, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 96, sprite_width, sprite_height));
		}
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

private:
	sf::Texture player_texture;
	uint32_t sprite_width = 48, sprite_height = 48;
	float speed = 1000.0f;
};