#pragma once

#include "system/Entity.h"
#include "../tiled2sfml/tiled2sfml.h"
#include "system/Animator.h"
#include "spdlog/spdlog.h"

class Character : public Entity
{
public:
	Character(const std::string& image_path, const sf::Vector2i& sprite_size);

	virtual void update(float dt);

	void move(const sf::Vector2f& dest);
	void setTilemap(Tiled2SFML& td);
	bool checkCollision(const sf::Vector2f& dest);
	void onCharacterMove(std::function<void()> func);

	Animator anim;
	sf::Sprite sprite;

protected:
	bool is_moving = false;
	float mov_elapsed_time = 0;
	float move_duration = 0.3f; // This can be adjusted for faster/slower movement
	sf::Vector2f move_target;
	sf::Vector2f move_direction; // New member for direction
private:
	std::shared_ptr<spdlog::logger> log;
	sf::Texture player_texture;

	std::function<void()> onCharacterMoveCallback;

	std::unique_ptr<Tiled2SFML> tiled2Sfml;

	sf::Vector2f move_destination;
	sf::Vector2f initial_position;
};