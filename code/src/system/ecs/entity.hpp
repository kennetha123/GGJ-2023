#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cassert>
#include <SFML/Graphics.hpp>

class animation_component;

class component
{
public:
	virtual ~component() = default;
};

class entity
{
public:
	entity() {}

	template<typename component_type, typename... component_args>
	std::shared_ptr<component_type> add_component(component_args&&... component_args_)
	{
		auto component = std::make_shared<component_type>(std::forward<component_args>(component_args_)...);
		components[std::type_index(typeid(component_type))] = component;
		return component;
	}

	template<typename component_type>
	std::shared_ptr<component_type> get_component()
	{
		auto component = components.find(std::type_index(typeid(component_type)));
		if (component != components.end())
		{
			return std::static_pointer_cast<component_type>(component->second);
		}
		return nullptr;
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<component>> components;
};

class animation_component : public component
{
public:
	animation_component(sf::Sprite& sprite, const std::vector<std::vector<sf::IntRect>>& frames, float frame_time) :
		sprite_(sprite), frames_(frames), frame_time_(frame_time) { }

	void update(float delta_time, int row)
	{
		if (row >= frames_.size())
		{
			return;
		}

		elapsed_time += delta_time;

		if (elapsed_time >= frame_time_)
		{
			elapsed_time = 0;
			current_frame = (current_frame + 1) % frames_[row].size();
			sprite_.setTextureRect(frames_[row][current_frame]);
		}
	}

private:
	sf::Sprite& sprite_;
	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_;
	float elapsed_time = 0;
	int current_frame = 0;
};
