#pragma once
#include "object.hpp"
#include "system/ecs/entity.hpp"
#include "animation.hpp"

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

		std::vector<std::vector<sf::IntRect>> all_frames = {
			{ // Down
				{48, 0, sprite_width, sprite_height},
				{0, 0, sprite_width, sprite_height},
				{48, 0, sprite_width, sprite_height},
				{96, 0, sprite_width, sprite_height},
			},
			{ // Left
				{48, 48, sprite_width, sprite_height},
				{0, 48, sprite_width, sprite_height},
				{48, 48, sprite_width, sprite_height},
				{96, 48, sprite_width, sprite_height},
			},
			{ // Right
				{48, 96, sprite_width, sprite_height},
				{0, 96, sprite_width, sprite_height},
				{48, 96, sprite_width, sprite_height},
				{96, 96, sprite_width, sprite_height},
			},
			{ // Up
				{48, 144, sprite_width, sprite_height},
				{0, 144, sprite_width, sprite_height},
				{48, 144, sprite_width, sprite_height},
				{96, 144, sprite_width, sprite_height},
			}
		};

		// Create the animated sprite objects
		player_animation = std::make_unique<animation>(player_sprite, all_frames, 0.25f);
	}

	~player() = default;

	void movement(float dt)
	{
		sf::Vector2f dest;

		int row = -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player_transform->move(-0.1f * dt * speed, 0.0f);
			row = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player_transform->move(0.0f, -0.1f * dt * speed);
			row = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player_transform->move(0.0f, 0.1f * dt * speed);
			row = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player_transform->move(0.1f * dt * speed, 0.0f);
			row = 2;
		}

		if (row != -1)
		{
			player_animation->update(dt, row);
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
	int sprite_width = 48, sprite_height = 48;
	float speed = 1000.0f;

	float elapsed_time = 0;

	std::unique_ptr<animation> player_animation;
};