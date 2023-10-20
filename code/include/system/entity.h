#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cassert>

class Component
{
public:
	virtual ~Component() = default;
};

class Entity
{
public:
	Entity() {}

	template<typename ComponentType, typename... ComponentArgs>
	std::shared_ptr<ComponentType> addComponent(ComponentArgs&&... component_args)
	{
		auto component = std::make_shared<ComponentType>(std::forward<ComponentArgs>(component_args)...);
		components[std::type_index(typeid(ComponentType))] = component;
		return component;
	}

	template<typename ComponentType>
	std::shared_ptr<ComponentType> getComponent()
	{
		auto component = components.find(std::type_index(typeid(ComponentType)));
		if (component != components.end())
		{
			return std::static_pointer_cast<ComponentType>(component->second);
		}
		return nullptr;
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};