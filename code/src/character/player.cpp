#include "character/Player.h"
#include "ServiceLocator.h"
#include "system/InputManager.h"
#include "utils/Logs.h"

Player::Player(const std::string& image_path, const sf::Vector2i& sprite_size) :
	Character(image_path, sprite_size)
{
	initKeyBindings();
	initAnimation();
}

void Player::update(float dt)
{
	Character::update(dt);

	controller.evaluateRules(anim);
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
	std::shared_ptr<KeyboardCommand> interact = std::make_shared<KeyboardCommand>([this]()
		{
			if (can_interact)
			{
				this->interact();
				can_interact = false;
			}
		}, [this]()
		{
			can_interact = true;
		});

	input.bindKeyToCmd(sf::Keyboard::Z, interact);
	input.bindKeyToCmd(sf::Keyboard::D, move_right);
	input.bindKeyToCmd(sf::Keyboard::A, move_left);
	input.bindKeyToCmd(sf::Keyboard::W, move_up);
	input.bindKeyToCmd(sf::Keyboard::S, move_down);
}

void Player::initAnimation()
{
	Animation idle_right;
	Animation idle_left;
	Animation idle_up;
	Animation idle_down;
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
				Logs::instance().log("anim", spdlog::level::debug, "walk Right");
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
				Logs::instance().log("anim", spdlog::level::debug, "walk Left");
				this->anim.PlayAnimation("Walk Left", sprite);
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
				Logs::instance().log("anim", spdlog::level::debug, "walk Up");
				this->anim.PlayAnimation("Walk Up", sprite);
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
				Logs::instance().log("anim", spdlog::level::debug, "walk down");
				this->anim.PlayAnimation("Walk Down", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[&](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) == 0.0f &&
						std::get<float>(animator.getParam("move_y")) == 0.0f &&
						last_direction.x > 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Idle Right", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[&](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) == 0.0f &&
						std::get<float>(animator.getParam("move_y")) == 0.0f &&
						last_direction.x < 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Idle Left", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[&](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) == 0.0f &&
						std::get<float>(animator.getParam("move_y")) == 0.0f &&
						last_direction.y < 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Idle Up", sprite);
			}
		});
	controller.addRule(
		AnimationRule{
			[&](const Animator& animator)
			{
					return std::get<float>(animator.getParam("move_x")) == 0.0f && 
						std::get<float>(animator.getParam("move_y")) == 0.0f && 
						last_direction.y > 0.0f;
			},
			[this]()
			{
				this->anim.PlayAnimation("Idle Down", sprite);
			}
		});

	idle_right.setFrame(
		{
			{ 48, 96, sprite_size.x, sprite_size.y }
		});
	idle_left.setFrame(
		{
			{ 48, 48, sprite_size.x, sprite_size.y }
		});
	idle_up.setFrame(
		{
			{ 48, 144, sprite_size.x, sprite_size.y }
		});

	idle_down.setFrame(
		{
			{ 48, 0, sprite_size.x, sprite_size.y }
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
			{48, 144, sprite_size.x, sprite_size.y},
			{0, 144, sprite_size.x, sprite_size.y},
			{48, 144, sprite_size.x, sprite_size.y},
			{96, 144, sprite_size.x, sprite_size.y},
		});
	walk_down.setFrame(
		{
			{48, 0, sprite_size.x, sprite_size.y},
			{0, 0, sprite_size.x, sprite_size.y},
			{48, 0, sprite_size.x, sprite_size.y},
			{96, 0, sprite_size.x, sprite_size.y},
		});

	anim.addAnimation("Idle Right", idle_right);
	anim.addAnimation("Idle Left", idle_left);
	anim.addAnimation("Idle Up", idle_up);
	anim.addAnimation("Idle Down", idle_down);
	anim.addAnimation("Walk Right", walk_right);
	anim.addAnimation("Walk Left", walk_left);
	anim.addAnimation("Walk Up", walk_up);
	anim.addAnimation("Walk Down", walk_down);

}

void Player::setNPC(NPCManager* npcm)
{
	npc_manager = npcm;
}

void Player::interact()
{
	sf::Vector2f interactionPos = sprite.getPosition() + last_direction;
	auto npc = npc_manager->getNPCAtPosition(interactionPos);
	if (npc) 
	{		
		on_dialog = npc->interact();
	}

	Logs::instance().log("NPC", spdlog::level::info, "interact with NPC : {}", on_dialog);
}