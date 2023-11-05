#pragma once

#include <memory>
#include "Character.h"
#include "system/Components.h"
#include "spdlog/spdlog.h"

class Player : public Character
{
public:
	Player(const std::string& image_path, const sf::Vector2i& sprite_size);
	~Player() = default;

    virtual void update(float dt) override;
	void initKeyBindings();
	void initAnimation();

	AnimationController controller;
	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_ = 0.15f;
	float anim_elapsed_time = 0;
	int current_frame = 0;
	int row = -1;
	int last_direction = 0;

	std::shared_ptr<spdlog::logger> log;
};