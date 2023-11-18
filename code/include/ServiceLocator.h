#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>

class ServiceLocator
{
public:
	template <typename ServiceType>
	static void provide(std::shared_ptr<ServiceType> service)
	{
		services[std::type_index(typeid(ServiceType))] = service;
	}

	template <typename ServiceType>
	static ServiceType& getService()
	{
		auto it = services.find(std::type_index(typeid(ServiceType)));

		if (it == services.end())
		{
			throw std::runtime_error("Handler not registered.");
		}
		return *std::static_pointer_cast<ServiceType>(it->second);
	}

	template <typename ServiceType>
	static void remove()
	{
		auto it = services.find(std::type_index(typeid(ServiceType)));
		if (it != services.end()) {
			services.erase(it);
		}
	}

private:
	static std::unordered_map<std::type_index, std::shared_ptr<void>> services;
};