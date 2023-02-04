#pragma once
#include "object.hpp"

class player : public object
{
public:
	player(const std::string& image_path) 
	{
		load_image(image_path);
	}

	~player()
	{

	}

	void movement()
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
			sprite.move(-0.1f, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sprite.move(0.0f, -0.1f);
			sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			sprite.move(0.0f, 0.1f);
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sprite.move(0.1f, 0.0f);
			sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
		}
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

private:
	
};