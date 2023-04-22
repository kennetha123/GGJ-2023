#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

namespace ui
{
	class fps_model
	{
	public:
		void set_fps(float fps) { this->fps = fps; }

		float get_fps() const { return fps; }

	private:
		float fps;
	};

	class fps_view
	{
	public:
		fps_view(const sf::Font& font)
		{
			fps_text.setFont(font);
			fps_text.setCharacterSize(32);
			fps_text.setFillColor(sf::Color::White);
			fps_text.setPosition(10, 10);
		}

		void update(float fps)
		{
			std::stringstream ss;
			ss << "FPS : " << static_cast<int>(fps);
			fps_text.setString(ss.str());
		}

		sf::Text get_text() 
		{
			return fps_text;
		}

	private:
		sf::Text fps_text;
	};
}