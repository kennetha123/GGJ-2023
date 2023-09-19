#include "character/Player.h"
#include <memory>
#include "../tiled2sfml/tiled2sfml.h"

Player::Player(const std::string& image_path)
{
    if (!player_texture.loadFromFile(image_path))
    {
        printf_s("Failed to load file!");
    }

    sprite.setTexture(player_texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setPosition(480.0, 480.0f);

    frames_ = {
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

    this->add_component<Collision>();
}

void Player::update(float dt)
{
    handleAnimation(dt);
    handleMovement(dt);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::handleAnimation(float dt)
{
	if (!is_moving)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			row = 1;
			last_direction = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			row = 3;
			last_direction = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			row = 0;
			last_direction = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			row = 2;
			last_direction = 2;
		}
		sprite.setTextureRect(frames_[last_direction][0]);
	}
	else
	{
		if (row != -1)
		{
			if (row >= frames_.size())
			{
				return;
			}

			anim_elapsed_time += dt;

			if (anim_elapsed_time >= frame_time_)
			{
				anim_elapsed_time = 0;
				current_frame = (current_frame + 1) % frames_[row].size();
				sprite.setTextureRect(frames_[row][current_frame]);
			}
		}
	}
}

// movement component

void Player::handleMovement(float dt)
{
	if (is_moving)
	{
		mov_elapsed_time += dt;
		float move_fraction = mov_elapsed_time / move_duration;

		if (move_fraction >= 1.0f)
		{
			is_moving = false;
			move_fraction = 1.0f;
		}

		sf::Vector2f pos = initial_position + sf::Vector2f(move_fraction * move_direction.x, move_fraction * move_direction.y);
		sprite.setPosition(pos);
	}
	else
	{
		sf::Vector2f dest;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dest = sf::Vector2f(-grid_size, 0.0f);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dest = sf::Vector2f(0.0f, -grid_size);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dest = sf::Vector2f(0.0f, grid_size);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dest = sf::Vector2f(grid_size, 0.0f);
			move(dest);
		}
	}
}

void Player::move(const sf::Vector2f& dest)
{
	if (!checkCollision(sprite.getPosition() + dest))
	{
		is_moving = true;
		move_direction = dest;
		initial_position = sprite.getPosition();
		mov_elapsed_time = 0;
	}
}

void Player::setTilemap(Tiled2SFML& tiled2Sfml_)
{
	tiled2Sfml = std::make_unique<Tiled2SFML>(tiled2Sfml_);
}

bool Player::checkCollision(const sf::Vector2f& dest)
{
	int idx = tiled2Sfml->positionToIndex(dest);
	if (tiled2Sfml->getTileDataId(idx).get_component<Collision>()->is_collide)
	{
		return true;
	}
	return false;
}