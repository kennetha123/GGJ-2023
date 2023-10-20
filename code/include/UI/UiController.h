#pragma once

#include <SFML/Graphics.hpp>
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
			std::string name;
			virtual void update(float dt) = 0;
			virtual void draw(sf::RenderWindow& window) = 0;
		};

		class FpsController : public BaseController
		{
		public:
			FpsController(const sf::Font& font);
			~FpsController();

			void update(float dt) override;
			void draw(sf::RenderWindow& window) override;

		private:
			View::FpsView fps_view;
			Model::FpsModel fps_model;

			int frame_count = 0;
			float fps_timer = 0;
		};

		class MainMenuController : public BaseController
		{
		public:
			MainMenuController(const sf::Font& font) :
				mm_view(font) {
				name = "main menu";
			}

			~MainMenuController() {}

			virtual void update(float dt) override;
			virtual void draw(sf::RenderWindow& window) override;
			void onClick();
			View::MainMenuView mm_view;

		private:
			Model::MainMenuModel mm_model;

		};
	}
}