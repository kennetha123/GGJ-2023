#include "character/NPC.h"
#include "json.hpp"
#include <random>

NPC::NPC(const std::string& name,
    const std::vector<std::string>& movement,
	bool is_loop,
    const sf::Vector2i& position,
    const std::string& dialog_path,
    const std::string& pic_path,
    const std::string& sprite_path) :
	Character(sprite_path, sf::Vector2i(48, 48)),
    _name(name),
    _movement(movement),
	_is_loop(is_loop),
    _dialog_path(dialog_path),
    _pic_path(pic_path)
{
    sprite.setPosition(sf::Vector2f(position.x, position.y));
	initAnimation();
}

void NPC::initAnimation()
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

void NPC::update(float dt)
{
    Character::update(dt);

	if (is_moving)
	{
		controller.evaluateRules(anim);
	}

	timer -= dt;
	if (timer <= 0)
	{
		if (_movement[0] == "random") 
		{
			moveRandomly();
		}
		else
		{
			if (current_movement_index < _movement.size())
			{
				std::string current_action = _movement[current_movement_index];
				if (movement_direction.find(current_action) != movement_direction.end())
				{
					move(movement_direction[current_action]);
					current_movement_index++;
				}
			}
			else
			{
				if (_is_loop || _movement[0] == "random")
				{
					current_movement_index = 0;
				}
			}
		}
		timer = 1.0f;
	}
}

void NPC::moveRandomly()
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	static std::uniform_int_distribution<int> uni(0, movement_direction.size() - 1);

	auto it = std::next(movement_direction.begin(), uni(rng));
	move(it->second);
}

NPCManager::NPCManager()
{

}

void NPCManager::setNPCScene(const std::string& json_file)
{
    auto log = spdlog::get("main");

    std::ifstream ifs(json_file);
    if (!ifs)
    {
        log->error("Could not open file for reading: {}", json_file);
        return;
    }
    
    json npc_data = json::parse(ifs, nullptr, false);
    if (npc_data.is_discarded())
    {
        log->error("Error parsing JSON data.", json_file);
        return;
    }

    for (const auto& item : npc_data)
    {
        sf::Vector2i pos(item["position"][0], item["position"][1]);
        auto npc = std::make_shared<NPC>(
            item["name"],
            item["movement"].get<std::vector<std::string>>(),
			item["is_loop"],
            pos,
            item["dialogue"],
            item["picture"],
            item["sprite"]
        );

        npcs.push_back(npc);
    }
}