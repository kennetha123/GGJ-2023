#include "character/Character.h"
#include "utils/Time.h"
#include "utils/Logs.h"

Character::Character(const std::string& image_path, const sf::Vector2i& sprite_sz)
{
	if (!player_texture.loadFromFile(image_path))
	{
		Logs::instance().log("character", spdlog::level::err, "Failed to load file!");
	}

	sprite.setTexture(player_texture);
	sprite_size = sprite_sz;
	sprite.setTextureRect(sf::IntRect(0, 0, sprite_size.x, sprite_size.y));
	this->addComponent<Collision>();
}

void Character::update(float dt)
{
	if (is_moving)
	{
		mov_elapsed_time += dw::Time::getDeltaTime();
		float move_fraction = mov_elapsed_time / move_duration;

		if (move_fraction >= 1.0f)
		{
			is_moving = false;
			is_anim_play = false;
			move_fraction = 1.0f;
		}

		sf::Vector2f pos = initial_position + sf::Vector2f(move_fraction * move_direction.x, move_fraction * move_direction.y);
		sprite.setPosition(pos);

		if (onCharacterMoveCallback)
		{
			onCharacterMoveCallback();
		}
	}

	if(!is_anim_play)
	{
		anim.setParam("move_x", 0.0f);
		anim.setParam("move_y", 0.0f);
	}
}

void Character::move(const sf::Vector2f& dest)
{
	is_anim_play = true;
	last_direction = dest;
	if (!is_moving)
	{
		sf::Vector2f destination = sprite.getPosition() + dest;

		if (!checkCollision(destination))
		{
			is_moving = true;
			move_direction = dest;
			initial_position = sprite.getPosition();
			mov_elapsed_time = 0;
			auto prev = tiled2Sfml->positionToIndex(sprite.getPosition());
			auto next = tiled2Sfml->positionToIndex(destination);
			tiled2Sfml->getTileData()[prev].getComponent<Collision>()->is_collide = false;
			tiled2Sfml->getTileData()[prev].getComponent<Collision>()->is_interactable = false;
			tiled2Sfml->getTileData()[next].getComponent<Collision>()->is_collide = true;
			tiled2Sfml->getTileData()[next].getComponent<Collision>()->is_interactable = true;
			anim.setParam("move_x", dest.x);
			anim.setParam("move_y", dest.y);
		}
		else
		{
			anim.setParam("move_x", 0.0f);
			anim.setParam("move_y", 0.0f);
			Logs::instance().log("character", spdlog::level::debug, "Collision ahead! {}:{}", destination.x, destination.y);
		}

	}
}

void Character::setTilemap(Tiled2SFML& tiled2Sfml_)
{
	tiled2Sfml = std::make_unique<Tiled2SFML>(tiled2Sfml_);
}

void Character::onCharacterMove(std::function<void()> func)
{
	onCharacterMoveCallback = func;
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
