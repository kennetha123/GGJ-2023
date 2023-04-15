#pragma once
#include "object.hpp"
#include "system/ecs/entity.hpp"

class player : public entity
{
public:
	player(const std::string& image_path) 
	{
		if (!player_texture.loadFromFile(image_path))
		{
			printf_s("Failed to load file!");
		}

		add_component<sprite_component>(player_texture);
		add_component<transform_component>(*this);
		transform_component& trans = *get_component<transform_component>();

		player_sprite = get_component<sprite_component>();
		player_transform = get_component<transform_component>();

		player_sprite->set_texture_rect(0, 0, sprite_width, sprite_height);
		player_transform->set_position(100.0f, 10.0f);
	}

	~player() = default;

	void movement(float dt)
	{
		sf::Vector2f dest;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player_transform->move(-0.1f * dt * speed, 0.0f);
			player_sprite->set_texture_rect(48, 48, sprite_width, sprite_height);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player_transform->move(0.0f, -0.1f * dt * speed);
			player_sprite->set_texture_rect(48, 144, sprite_width, sprite_height);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player_transform->move(0.0f, 0.1f * dt * speed);
			player_sprite->set_texture_rect(48, 0, sprite_width, sprite_height);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player_transform->move(0.1f * dt * speed, 0.0f);
			player_sprite->set_texture_rect(48, 96, sprite_width, sprite_height);
		}
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(player_sprite->get_sprite());
	}

private:
	std::shared_ptr<sprite_component> player_sprite;
	std::shared_ptr<transform_component> player_transform;
	sf::Texture player_texture;
	uint32_t sprite_width = 48, sprite_height = 48;
	float speed = 1000.0f;
};