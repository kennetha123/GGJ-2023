#pragma once

#include "UI/UiView.h"
#include <string>
#include <sstream>
#include <iostream>
#include "ServiceLocator.h"
#include "render/RENDERER.H"
#include "utils/Localization.h"
#include "utils/Logs.h"
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

		MainMenuView::MainMenuView(const sf::Font& font)
		{
			auto loc = ServiceLocator::getService<Localization>();

			const std::string button_path = "../resources/UI/main_menu_button.png";
			new_game_button = std::make_shared<Button>(button_path, font, loc.getText("new_game", "en"), 200, 680);
			load_game_button = std::make_shared <Button>(button_path, font, loc.getText("load_game", "en"), 500, 680);
			settings_button = std::make_shared <Button>(button_path, font, loc.getText("settings", "en"), 800, 680);
			quit_button = std::make_shared <Button>(button_path, font, loc.getText("quit", "en"), 1100, 680);

			auto& render = ServiceLocator::getService<RenderManager>();

			render.addDrawable(*new_game_button, *new_game_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(*load_game_button, *load_game_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(*settings_button, *settings_button, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(*quit_button, *quit_button, RenderLayer::UI, RenderBehavior::STATIC);

		}

		MainMenuView::~MainMenuView()
		{

		}

		void MainMenuView::update(const Model::Model& model_)
		{

		}

		DialogBoxView::DialogBoxView()
		{
			box.setFillColor(sf::Color::White);
			box.setSize(sf::Vector2f(600, 200));
		}

		void DialogBoxView::setText(const std::wstring& txt, const sf::Font& font)
		{
			display_text.setFont(font);
			display_text.setString(txt);
			display_text.setCharacterSize(30);
			display_text.setFillColor(sf::Color::Black);
			display_text.setPosition(box.getPosition().x, box.getPosition().y);
		}

		void DialogBoxView::update(const Model::Model& model_)
		{
		}
	}
}