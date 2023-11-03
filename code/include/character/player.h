#pragma once

#include <memory>
#include "Character.h"

class Player : public Character
{
public:
    Player(const std::string& image_path, const sf::Vector2i& sprite_size);
    ~Player() = default;

    virtual void update(float dt) override;
	void setupKeyBindings();
	void initKeyBindings();
	void initAnimation();

private:

	AnimationController controller;
	std::vector<std::vector<sf::IntRect>> frames_;
};