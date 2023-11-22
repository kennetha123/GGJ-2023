#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "UiModel.h"

namespace UI
{
	namespace View
	{
		class View
		{
		public:
			virtual void update(const Model::Model& model_) = 0;
		};

		class FpsView : public View
		{
		public:
			FpsView(const sf::Font& font);
			void update(const Model::Model& model_) override;

		private:
			sf::Text fps_text;
		};

		class MainMenuView : public View
		{
		public:
			MainMenuView(const sf::Font& font);
			~MainMenuView();

			virtual void update(const Model::Model& model_) override;

		public:
			std::shared_ptr<Button> new_game_button;
			std::shared_ptr<Button> load_game_button;
			std::shared_ptr<Button> settings_button;
			std::shared_ptr<Button> quit_button;
		};

		class DialogBoxView : public View
		{
		public:
			DialogBoxView();
			~DialogBoxView() {};
			virtual void update(const Model::Model& model_) override;
			void setText(const std::wstring& txt, const sf::Font& font);
			std::string getText();
			sf::RectangleShape box;
			sf::Text display_text;
		};
	}
}