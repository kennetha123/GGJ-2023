#include "system/components.h"

void animation_component::update(float delta_time, int row)
{
	if (row >= frames_.size())
	{
		return;
	}

	elapsed_time += delta_time;

	if (elapsed_time >= frame_time_)
	{
		elapsed_time = 0;
		current_frame = (current_frame + 1) % frames_[row].size();
		sprite_.setTextureRect(frames_[row][current_frame]);
	}
}

void animation_component::handle_animation(float dt, int row)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		row = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		row = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		row = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		row = 2;
	}

	if (row != -1)
	{
		update(dt, row);
	}
}

// movement component

void movement_component::handle_movement(float dt)
{
	if (is_moving)
	{
		elapsed_time += dt;
		float move_fraction = elapsed_time / move_duration;

		if (move_fraction >= 1.0f)
		{
			is_moving = false;
			move_fraction = 1.0f;
		}

		sprite_.setPosition(initial_position + sf::Vector2f(move_fraction * move_direction.x, move_fraction * move_direction.y));
	}
	else
	{
		sf::Vector2f dest;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dest = sf::Vector2f(-grid_size, 0.0f);
			if (!tile_manager_->check_collision(sprite_.getPosition() + dest))
			{
				is_moving = true;
				move_direction = dest;
				initial_position = sprite_.getPosition();
				elapsed_time = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dest = sf::Vector2f(0.0f, -grid_size);
			if (!tile_manager_->check_collision(sprite_.getPosition() + dest))
			{
				is_moving = true;
				move_direction = dest;
				initial_position = sprite_.getPosition();
				elapsed_time = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dest = sf::Vector2f(0.0f, grid_size);
			if (!tile_manager_->check_collision(sprite_.getPosition() + dest))
			{
				is_moving = true;
				move_direction = dest;
				initial_position = sprite_.getPosition();
				elapsed_time = 0;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dest = sf::Vector2f(grid_size, 0.0f);
			if (!tile_manager_->check_collision(sprite_.getPosition() + dest))
			{
				is_moving = true;
				move_direction = dest;
				initial_position = sprite_.getPosition();
				elapsed_time = 0;
			}

		}
	}
}

void movement_component::set_tile_manager(std::shared_ptr<tile_manager> tile_mgr)
{
	tile_manager_ = tile_mgr;
}
