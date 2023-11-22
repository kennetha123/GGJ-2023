#pragma once

#include "system/Entity.h"
#include "../tiled2sfml/tiled2sfml.h"
#include "system/Animator.h"

class Character : public Entity
{
public:
	Character(const std::string& image_path, const sf::Vector2i& sprite_sz);

	virtual void update(float dt);
	void setTilemap(Tiled2SFML& td);
	bool checkCollision(const sf::Vector2f& dest);
	void move(const sf::Vector2f& dest);
	void onCharacterMove(std::function<void()> func);

	sf::Sprite sprite;
	bool on_dialog = false;

protected:

	Animator anim;
	bool is_moving = false;
	bool is_anim_play = false;
	sf::Vector2i sprite_size;
	std::unique_ptr<Tiled2SFML> tiled2Sfml;
	sf::Vector2f move_direction;
	sf::Vector2f last_direction;

private:

	std::function<void()> onCharacterMoveCallback;
	sf::Texture player_texture;

	sf::Vector2f initial_position;

	float move_duration = 0.3f;
	float mov_elapsed_time = 0;
};