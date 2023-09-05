#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cassert>

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