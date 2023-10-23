#pragma once

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include "ServiceLocator.h"
#include "UiView.h"
#include "UiModel.h"

namespace UI
{
	namespace Controller
	{
		class BaseController
		{
		public:
			virtual void update(float dt) = 0;
			virtual void static_draw(sf::RenderTexture& render_tex) = 0;
			virtual void dynamic_draw(sf::RenderWindow& window) = 0;
		};

		class FpsController : public BaseController
		{
		public:
			FpsController(const sf::Font& font);
			~FpsController();

			void update(float dt) override;
			void static_draw(sf::RenderTexture& render_tex) override;
			void dynamic_draw(sf::RenderWindow& window) override;

		private:
			std::shared_ptr<spdlog::logger> log;

			View::FpsView fps_view;
			Model::FpsModel fps_model;

			int frame_count = 0;
			float fps_timer = 0;
		};

		class MainMenuController : public BaseController
		{
		public:
			MainMenuController(const sf::Font& font);
			~MainMenuController();

			virtual void update(float dt) override;
			void static_draw(sf::RenderTexture& render_tex) override;
			void dynamic_draw(sf::RenderWindow& window) override;
			void onClick();
			View::MainMenuView mm_view;

		private:
			std::shared_ptr<spdlog::logger> log;

			Model::MainMenuModel mm_model;

		};
	}
}