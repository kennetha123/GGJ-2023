#include "character/Character.h"
#include "utils/Time.h"

Character::Character(const std::string& image_path, const sf::Vector2i& sprite_sz)
{
	if (!player_texture.loadFromFile(image_path))
	{
		printf_s("Failed to load file!");
	}

	sprite.setTexture(player_texture);
	sprite.setTextureRect(sf::IntRect(0, 0, sprite_size.x, sprite_size.y));
	sprite_size = sprite_sz;
	this->addComponent<Collision>();
}

void Character::handleMovement()
{
	if (is_moving)
	{
		mov_elapsed_time += dw::Time::getDeltaTime();
		float move_fraction = mov_elapsed_time / move_duration;

		if (move_fraction >= 1.0f)
		{
			is_moving = false;
			move_fraction = 1.0f;
		}

		sf::Vector2f pos = initial_position + sf::Vector2f(move_fraction * move_direction.x, move_fraction * move_direction.y);
		sprite.setPosition(pos);

		if (onCharacterMoveCallback)
		{
			onCharacterMoveCallback();
		}

	}
	else
	{
		sf::Vector2f dest;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dest = sf::Vector2f(-48.0f, 0.0f);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dest = sf::Vector2f(0.0f, -48.0f);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dest = sf::Vector2f(0.0f, 48.0f);
			move(dest);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dest = sf::Vector2f(48.0f, 0.0f);
			move(dest);
		}
	}
}

void Character::move(const sf::Vector2f& dest)
{
	if (!checkCollision(sprite.getPosition() + dest))
	{
		is_moving = true;
		move_direction = dest;
		initial_position = sprite.getPosition();
		mov_elapsed_time = 0;
	}

	anim.setParam("move_x", move_direction.x);
	anim.setParam("move_y", move_direction.y);
}

void Character::setTilemap(Tiled2SFML& tiled2Sfml_)
{
	tiled2Sfml = std::make_unique<Tiled2SFML>(tiled2Sfml_);
}

bool Character::checkCollision(const sf::Vector2f& dest)
{
	int idx = tiled2Sfml->positionToIndex(dest);
	if (tiled2Sfml->getTileDataId(idx).getComponent<Collision>()->is_collide)
	{
		return true;
	}
	return false;
}

void Character::onCharacterMove(std::function<void()> func)
{
	onCharacterMoveCallback = func;
}