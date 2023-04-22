#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cassert>
#include <SFML/Graphics.hpp>

class transform_component;
class sprite_component;
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

	sprite_component()
	{
		std::cout << "you haven't set texture. Make sure you set it later." << std::endl;
	}

	void set_texture_rect(int rect_left, int rect_top, int rect_width, int rect_height)
	{
		sprite.setTextureRect(sf::IntRect(rect_left, rect_top, rect_width, rect_height));
	}

	void set_texture_rect(const sf::IntRect& rect)
	{
		sprite.setTextureRect(rect);
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
	/// <summary>
	/// The constructor is required for make sure the sprite component
	/// is exist and cannot be modified directly through the sprite component.
	/// These are limitation coming from SFML that use inheritance so when implementing
	/// ECS it's not possible to divide the transform component and sprite easily.
	/// </summary>
	/// <param name="parent">entity class that already added sprite component.</param>
	transform_component(entity& parent) : parent_(parent) 
	{
		sprite_comp = parent_.get_component<sprite_component>();
		assert(sprite_comp && "sprite component is not exist in entity object!");
	}

	void set_position(float x, float y)
	{
		sprite_comp->set_position(x, y);
	}

	void set_position(sf::Vector2f vec)
	{
		sprite_comp->set_position(vec.x, vec.y);
	}

	void move(float offset_x, float offset_y)
	{
		sprite_comp->move(offset_x, offset_y);
	}

	const sf::Vector2f get_position() const
	{
		return sprite_comp->sprite.getPosition();
	}
private:
	entity& parent_;
	std::shared_ptr<sprite_component> sprite_comp;
};

class animation_component : public component
{
public:
	animation_component(std::shared_ptr<sprite_component> sprite_comp, const std::vector<std::vector<sf::IntRect>>& frames, float frame_time) :
		sprite_comp_(sprite_comp), frames_(frames), frame_time_(frame_time) { }

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
			sprite_comp_->set_texture_rect(frames_[row][current_frame]);
		}
	}

private:
	std::shared_ptr<sprite_component> sprite_comp_;
	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_;
	float elapsed_time = 0;
	int current_frame = 0;
};
