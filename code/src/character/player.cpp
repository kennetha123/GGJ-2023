#include "character/Player.h"
#include "ServiceLocator.h"
#include "system/InputManager.h"

Player::Player(const std::string& image_path, const sf::Vector2i& sprite_size) :
	Character(image_path, sprite_size)
{
	log = spdlog::get("main");
	initKeyBindings();
	initAnimation();
}

void Player::update(float dt)
{
	Character::update(dt);

	if (is_moving)
	{
		controller.evaluateRules(anim);
	}
}

void Player::initKeyBindings()
{
	InputManager& input = ServiceLocator::getService<InputManager>();

	std::shared_ptr<KeyboardCommand> move_right = std::make_shared<KeyboardCommand>([&]() 
		{
			move(sf::Vector2f(48.0f, 0.0f));
		});
	std::shared_ptr<KeyboardCommand> move_left = std::make_shared<KeyboardCommand>([&]() 
		{
			move(sf::Vector2f(-48.0f, 0.0f));
		});
	std::shared_ptr<KeyboardCommand> move_up = std::make_shared<KeyboardCommand>([&]() 
		{
			move(sf::Vector2f(0.0f, -48.0f));
		});
	std::shared_ptr<KeyboardCommand> move_down = std::make_shared<KeyboardCommand>([&]() 
		{
			move(sf::Vector2f(0.0f, 48.0f));
		});

	input.bindKeyToCmd(sf::Keyboard::D, move_right);
	input.bindKeyToCmd(sf::Keyboard::A, move_left);
	input.bindKeyToCmd(sf::Keyboard::W, move_up);
	input.bindKeyToCmd(sf::Keyboard::S, move_down);
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
			sf::IntRect(48, 96, sprite_size.x, sprite_size.y),
			sf::IntRect(0, 96, sprite_size.x, sprite_size.y),
			sf::IntRect(48, 96, sprite_size.x, sprite_size.y),
			sf::IntRect(96, 96, sprite_size.x, sprite_size.y),
		});
	walk_left.setFrame(
		{
			{48, 48, sprite_size.x, sprite_size.y},
			{0, 48, sprite_size.x, sprite_size.y},
			{48, 48, sprite_size.x, sprite_size.y},
			{96, 48, sprite_size.x, sprite_size.y},
		});
	walk_up.setFrame(
		{
			{48, 0, sprite_size.x, sprite_size.y},
			{0, 0, sprite_size.x, sprite_size.y},
			{48, 0, sprite_size.x, sprite_size.y},
			{96, 0, sprite_size.x, sprite_size.y},

		});
	walk_down.setFrame(
		{
			{48, 144, sprite_size.x, sprite_size.y},
			{0, 144, sprite_size.x, sprite_size.y},
			{48, 144, sprite_size.x, sprite_size.y},
			{96, 144, sprite_size.x, sprite_size.y},

		});

	anim.addAnimation("Idle", idle);
	anim.addAnimation("Walk Right", walk_right);
	anim.addAnimation("Walk Left", walk_left);
	anim.addAnimation("Walk Up", walk_up);
	anim.addAnimation("Walk Down", walk_down);

}