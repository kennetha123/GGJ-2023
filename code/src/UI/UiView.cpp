#pragma once

#include "UI/UiView.h"
#include <string>
#include <sstream>
#include <iostream>

namespace UI
{
	namespace View
	{
		FpsView::FpsView(const sf::Font& font)
		{
			fps_text.setFont(font);
			fps_text.setCharacterSize(32);
			fps_text.setFillColor(sf::Color::White);
			fps_text.setPosition(10, 10);
		}

		void FpsView::update(const Model::Model& model_)
		{
			const Model::FpsModel& fps_model = dynamic_cast<const Model::FpsModel&>(model_);

			std::stringstream ss;
			ss << "FPS : " << static_cast<int>(fps_model.getFps());
			fps_text.setString(ss.str());
		}

		void FpsView::draw(sf::RenderWindow& window)
		{
			window.draw(fps_text);
		}


		void MainMenuView::update(const Model::Model& model_)
		{

		}

		void MainMenuView::draw(sf::RenderWindow& window)
		{
			window.draw(new_game_button);
			window.draw(load_game_button);
			window.draw(settings_button);
			window.draw(quit_button);
		}

		void MainMenuView::setMenuOption(sf::Text& text, const sf::Font& font, const std::string& str, float x, float y)
		{
			text.setFont(font);
			text.setString(str);
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::White);
			text.setPosition(x, y);
		}
	}
}