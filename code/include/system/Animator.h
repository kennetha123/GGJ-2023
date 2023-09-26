#pragma once
#include <map>
#include <any>
#include <string>
#include <vector>
#include <variant>
#include <SFML/Graphics.hpp>
#include <functional>

class Animation
{
public:
	Animation() = default;
	Animation& operator=(const Animation&) = default;
	Animation& operator=(Animation&&) = default;

	void Play(const std::string& anime_name, sf::Sprite& sprite);
	inline void setSpeed(float speed_)
	{
		speed = speed_;
	}

	void setFrame(const std::vector<sf::IntRect>& frame);
private:
	float speed = 5.0f;
	float delta_time = 0.0f;
	float elapsed_time = 0;
	int current_frame = 0;
	std::vector<sf::IntRect> frames;

};

class Animator
{
public:
	inline void addAnimation(const std::string& anim_name, const Animation& anim)
	{
		animations[anim_name] = anim;
	}

	void PlayAnimation(const std::string& anim_name, sf::Sprite& sprite);

	inline void setParam(const std::string& param_name, const std::variant<int, float, bool>& param)
	{
		parameters[param_name] = param;
	}

	inline std::variant<int, float, bool> getParam(const std::string& param_name) const
	{
		return parameters.at(param_name);
	}

private:
	std::map<std::string, std::variant<int, float, bool>> parameters;
	std::map<std::string, Animation> animations;
};

class AnimationRule
{
public:
	using Condition = std::function<bool(const Animator&)>;
	using Action = std::function<void()>;

	AnimationRule(Condition condition_, Action action_) : condition(condition_), action(action_) {}

	bool evaluate(const Animator& anim)
	{
		if (condition(anim))
		{
			action();
			return true;
		}
		return false;
	}

private:
	Condition condition;
	Action action;
};

class AnimationController
{
public:
	void addRule(AnimationRule rule)
	{
		rules.push_back(rule);
	}

	void evaluateRules(const Animator& anim)
	{
		for (auto& rule : rules)
		{
			if (rule.evaluate(anim))
			{
				break;
			}
		}
	}

private:
	std::vector<AnimationRule> rules;
};