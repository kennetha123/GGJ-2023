#pragma once
#include <typeindex>
#include <unordered_map>
#include <memory>
//#include <SFML/Graphics.hpp>
//
//#include "ui/ui_manager.hpp"
//#include "audio/audio_manager.h"
//#include "system/input_handler.hpp"
//#include "system/game_event_handler.hpp"

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

private:
	static std::unordered_map<std::type_index, std::shared_ptr<void>> services;
};