#pragma once

#include "UI/UiView.h"
#include <string>
#include <sstream>
#include <iostream>
#include "ServiceLocator.h"
#include "render/RENDERER.H"

namespace UI
{
	namespace View
	{
		FpsView::FpsView(const sf::Font& font)
		{
			fps_text.setFont(font);
			fps_text.setCharacterSize(32);
			fps_text.setFillColor(sf::Color::White);

			auto& render = ServiceLocator::getService<RenderManager>();
			render.addDrawable(fps_text, fps_text, RenderLayer::UI, RenderBehavior::DYNAMIC);
		}

		void FpsView::update(const Model::Model& model_)
		{
			sf::View& camera = ServiceLocator::getService<RenderManager>().getCamera();
			sf::Vector2f cam_pos = camera.getCenter() - 0.5f * camera.getSize();
			fps_text.setPosition(cam_pos.x + 10, cam_pos.y + 10);

			const Model::FpsModel& fps_model = dynamic_cast<const Model::FpsModel&>(model_);

			std::stringstream ss;
			ss << "FPS : " << static_cast<int>(fps_model.getFps());
			fps_text.setString(ss.str());
		}

		MainMenuView::MainMenuView(const sf::Font& font) :
			new_game_button(font, "New Game", 100, 100),
			load_game_button(font, "Load Game", 100, 150),
			settings_button(font, "Settings", 100, 200),
			quit_button(font, "Quit", 100, 250)
		{
			auto& render = ServiceLocator::getService<RenderManager>();

			render.addDrawable(new_game_button, new_game_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(load_game_button, load_game_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(settings_button, settings_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(quit_button, quit_button, RenderLayer::UI, RenderBehavior::STATIC);
		}

		void MainMenuView::update(const Model::Model& model_)
		{

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