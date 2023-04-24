#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include <string>
#include <sstream>

namespace ui
{
	namespace model
	{
		class model
		{
		public:
			virtual ~model() = default;
		};

		class fps_model : public model
		{
		public:
			void set_fps(float fps)
			{
				this->fps = fps;
			}

			float get_fps() const
			{
				return fps;
			}

		private:
			float fps = 0;
		};

		class main_menu_model : public model
		{
		};
	}

	namespace view
	{
		class view
		{
		public:
			virtual void update(const model::model& model_) = 0;
			virtual void draw(sf::RenderWindow& window) = 0;
		};

		class fps_view : public view
		{
		public:
			fps_view(const sf::Font& font)
			{
				fps_text.setFont(font);
				fps_text.setCharacterSize(32);
				fps_text.setFillColor(sf::Color::White);
				fps_text.setPosition(10, 10);
			}

			void update(const model::model& model_) override
			{
				const model::fps_model& fps_model = dynamic_cast<const model::fps_model&>(model_);

				std::stringstream ss;
				ss << "FPS : " << static_cast<int>(fps_model.get_fps());
				fps_text.setString(ss.str());
			}

			void draw(sf::RenderWindow& window) override
			{
				window.draw(fps_text);
			}

		private:
			sf::Text fps_text;
		};

		class main_menu_view : public view
		{
		public:
			main_menu_view(const sf::Font& font) :
				settings_button(font, "Settings", 50, 250)
			{
				set_menu_option(newGameText, font, "New Game", 50, 100);
				set_menu_option(loadGameText, font, "Load Game", 50, 150);
				set_menu_option(quitText, font, "Quit", 50, 200);
				set_menu_option(optionsText, font, "Options", 800 - 200, 10);
			}

			virtual void update(const model::model& model_) override
			{

			}

			virtual void draw(sf::RenderWindow& window) override
			{
				window.draw(newGameText);
				window.draw(loadGameText);
				window.draw(quitText);
				window.draw(optionsText);

				window.draw(settings_button);
			}

		private:
			void set_menu_option(sf::Text& text, const sf::Font& font, const std::string& str, float x, float y)
			{
				text.setFont(font);
				text.setString(str);
				text.setCharacterSize(30);
				text.setFillColor(sf::Color::White);
				text.setPosition(x, y);
			}

		public:
			Button settings_button;

		private:
			sf::Text newGameText;
			sf::Text loadGameText;
			sf::Text quitText;
			sf::Text optionsText;

		};
	}

	namespace controller
	{
		class base_controller
		{
		public:
			virtual void update(float dt) = 0;
			virtual void draw(sf::RenderWindow& window) = 0;
		};

		class fps_controller : public base_controller
		{
		public:
			fps_controller(const sf::Font& font) : fps_view_(font) {}

			void update(float dt) override
			{
				fps_timer += dt;
				frame_count++;

				if (fps_timer >= 1.0f)
				{
					int fps = static_cast<int>(frame_count / fps_timer);
					fps_model_.set_fps(fps);
					fps_view_.update(fps_model_);
					frame_count = 0;
					fps_timer = 0;
				}
			}

			void draw(sf::RenderWindow& window) override
			{
				fps_view_.draw(window);
			}

		private:
			view::fps_view fps_view_;
			model::fps_model fps_model_;

			int frame_count = 0;
			float fps_timer = 0;
		};

		class main_menu_controller : public base_controller
		{
		public:
			main_menu_controller(const sf::Font& font) : 
				mm_view_(font)
			{

			}

			virtual void update(float dt) override
			{

			}

			virtual void draw(sf::RenderWindow& window) override
			{
				mm_view_.draw(window);
			}
			view::main_menu_view mm_view_;

		private:
			model::main_menu_model mm_model_;

		};
	}
}