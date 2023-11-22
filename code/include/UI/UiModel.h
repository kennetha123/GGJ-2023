#pragma once
#include <SFML/Graphics.hpp>

namespace UI
{
	namespace Model
	{
		class Model
		{
		public:
			virtual ~Model() = default;
		};

		class FpsModel : public Model
		{
		public:
			void setFps(float fps);
			float getFps() const;

		private:
			float fps = 0;
		};

		class MainMenuModel : public Model
		{
		};

		class SettingsMenuModel : public Model
		{
		public:
			void setResolution(int x, int y);
			void setResolution(sf::Vector2i size);
			sf::Vector2i getResolution() const;

			void setLanguage(std::string& lang);
			std::string getLanguage() const;

		private:
			sf::Vector2i resolution;
			std::string language;
		};

		class DialogBoxModel : public Model
		{

		};
	}

}