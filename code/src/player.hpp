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
	}

	~player()
	{

	}

	void movement(float dt)
	{
		sf::Vector2f dest;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			//// Get the current time
			//auto now = std::chrono::high_resolution_clock::now();
			//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
			//int milliseconds = duration.count();

			//// Calculate the position based on the time
			//float x = sprite.getPosition().x;
			//x = (-10 * milliseconds) / 1000.0f;
			//if (x < -10) x = -10;
			//sprite.setPosition(x, sprite.getPosition().y);
		}

	//	printf_s("Renderer : %f\n", sprite.getPosition().x);
	//	printf_s("dest : %f\n", dest.x);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sprite.move(-0.1f * dt * speed, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 48, x, y));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sprite.move(0.0f, -0.1f * dt * speed);
			sprite.setTextureRect(sf::IntRect(0, 144, x, y));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sprite.move(0.0f, 0.1f * dt * speed);
			sprite.setTextureRect(sf::IntRect(0, 0, x, y));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sprite.move(0.1f * dt * speed, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 96, x, y));
		}
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

private:
	sf::Texture player_texture;
	uint32_t x = 48, y = 48;
	float speed = 1000.0f;
};