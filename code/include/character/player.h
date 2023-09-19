#pragma once
#include "system/components.h"
#include <memory>
#include "../tiled2sfml/tiled2sfml.h"

class Player : public entity
{
public:
    Player(const std::string& image_path);
    ~Player() = default;

    void update(float dt);
    void draw(sf::RenderWindow& window);
	void handleAnimation(float dt);
	void handleMovement(float dt);
	void move(const sf::Vector2f& dest);
	void setTilemap(Tiled2SFML& td);
	bool checkCollision(const sf::Vector2f& dest);

	sf::Sprite sprite;
private:
	std::unique_ptr<Tiled2SFML> tiled2Sfml;

    sf::Texture player_texture;
    int sprite_width = 48, sprite_height = 48;

	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_ = 0.15f;
	float anim_elapsed_time = 0;
	float mov_elapsed_time = 0;
	int current_frame = 0;
	int row = -1;
	int last_direction = 0;

	bool is_moving = false;
	sf::Vector2f initial_position;
	sf::Vector2f move_direction;
	float grid_size = 48.0f;
	float move_duration = 0.3f;
};