#pragma once
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

#include <typeindex>

class transform_component;
class sprite_component;

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
	void add_component(component_args&&... component_args_)
	{
		components[std::type_index(typeid(component_type))] = std::make_shared<component_type>(std::forward<component_args>(component_args_)...);
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

class sprite_component : public component
{
public:
	sprite_component(const sf::Texture& texture) : sprite(texture) {}

	void set_texture_rect(int rect_left, int rect_top, int rect_width, int rect_height)
	{
		sprite.setTextureRect(sf::IntRect(rect_left, rect_top, rect_width, rect_height));
	}

	const sf::Sprite& get_sprite() const
	{
		return sprite;
	}
private:
	sf::Sprite sprite;

	friend class transform_component;
	void set_position(float x, float y)
	{
		sprite.setPosition(x, y);
	}

	void move(float offset_x, float offset_y)
	{
		sprite.move(offset_x, offset_y);
	}

};

class transform_component : public component
{
public:
	transform_component(entity& parent) : parent_(parent) {}
	void set_position(float x, float y)
	{
		auto sprite_comp = parent_.get_component<sprite_component>();
		if (sprite_comp)
		{
			sprite_comp->set_position(x, y);
		}
	}

	void move(float offset_x, float offset_y)
	{
		auto sprite_comp = parent_.get_component<sprite_component>();
		if (sprite_comp)
		{
			sprite_comp->move(offset_x, offset_y);
		}
	}
private:
	entity& parent_;
};

