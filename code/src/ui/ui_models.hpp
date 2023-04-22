#pragma once

#include <SFML/Graphics.hpp>

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
	}
}