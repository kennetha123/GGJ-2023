#include "character/Player.h"
#include "utils/Time.h"
#include "ServiceLocator.h"
#include "system/InputManager.h"

Player::Player(const std::string& image_path)
{
    if (!player_texture.loadFromFile(image_path))
    {
        printf_s("Failed to load file!");
    }

    sprite.setTexture(player_texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setPosition(480.0, 480.0f);

    this->addComponent<Collision>();

	initKeyBindings();
	initAnimation();
}

void Player::update(float dt)
{
	if (is_moving)
	{
		controller.evaluateRules(anim);
	}
	
	handleMovement();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Player::initKeyBindings()
{
	std::shared_ptr<MoveRightCommand> move_right = std::make_shared<MoveRightCommand>();
	ServiceLocator::getService<InputManager>().bindKeyToCmd(sf::Keyboard::D, move_right);
}

void Player::initAnimation()
{
	Animation idle;
	Animation walk_right;
	Animation walk_left;
	Animation walk_up;
	Animation walk_down;

	controller.addRule(
		AnimationRule{
			[](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) > 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Walk Right", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) < 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Walk Left", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_y")) > 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Walk Up", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_y")) < 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Walk Down", sprite);
			}
		});

	walk_right.setFrame(
		{
			sf::IntRect(48, 96, sprite_width, sprite_height),
			sf::IntRect(0, 96, sprite_width, sprite_height),
			sf::IntRect(48, 96, sprite_width, sprite_height),
			sf::IntRect(96, 96, sprite_width, sprite_height),
		});
	walk_left.setFrame(
		{
			{48, 48, sprite_width, sprite_height},
			{0, 48, sprite_width, sprite_height},
			{48, 48, sprite_width, sprite_height},
			{96, 48, sprite_width, sprite_height},
		});
	walk_up.setFrame(
		{
			{48, 0, sprite_width, sprite_height},
			{0, 0, sprite_width, sprite_height},
			{48, 0, sprite_width, sprite_height},
			{96, 0, sprite_width, sprite_height},

		});
	walk_down.setFrame(
		{
			{48, 144, sprite_width, sprite_height},
			{0, 144, sprite_width, sprite_height},
			{48, 144, sprite_width, sprite_height},
			{96, 144, sprite_width, sprite_height},

		});

	anim.addAnimation("Idle", idle);
	anim.addAnimation("Walk Right", walk_right);
	anim.addAnimation("Walk Left", walk_left);
	anim.addAnimation("Walk Up", walk_up);
	anim.addAnimation("Walk Down", walk_down);

}

// movement component

void Player::handleMovement()
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

		if (onPlayerMoveCallback)
		{
			onPlayerMoveCallback();
		}
	}

	anim.setParam("move_x", move_direction.x);
	anim.setParam("move_y", move_direction.y);
}

void Player::setTilemap(Tiled2SFML& tiled2Sfml_)
{
	tiled2Sfml = std::make_unique<Tiled2SFML>(tiled2Sfml_);
}

bool Player::checkCollision(const sf::Vector2f& dest)
{
	int idx = tiled2Sfml->positionToIndex(dest);
	if (tiled2Sfml->getTileDataId(idx).getComponent<Collision>()->is_collide)
	{
		return true;
	}
	return false;
}

void Player::onPlayerMove(std::function<void()> func)
{
	onPlayerMoveCallback = func;
}