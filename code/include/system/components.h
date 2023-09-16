#pragma once
#include "system/entity.h"
#include <SFML/Graphics.hpp>
#include "system/tile_manager.h"
class animation_component;

class animation_component : public component
{
public:
	animation_component(sf::Sprite& sprite, const std::vector<std::vector<sf::IntRect>>& frames, float frame_time) :
		sprite_(sprite), frames_(frames), frame_time_(frame_time) { }

	void update(float delta_time, int row);
	void handle_animation(float dt, int row);

private:
	sf::Sprite& sprite_;
	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_;
	float elapsed_time = 0;
	int current_frame = 0;
};

class movement_component : public component
{
public:
	movement_component(sf::Sprite& sprite) :
		sprite_(sprite) { }

	void handle_movement(float dt);
	void set_tile_manager(std::shared_ptr<tile_manager> tile_mgr);
private:
	sf::Sprite& sprite_;
	std::shared_ptr<tile_manager> tile_manager_;
	bool is_moving = false;
	sf::Vector2f initial_position;
	sf::Vector2f move_direction;
	float elapsed_time = 0;
	float grid_size = 48.0f;
	float move_duration = 0.3f;
};