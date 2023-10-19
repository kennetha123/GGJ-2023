#include "ServiceLocator.h"
#include "system/entity.h"
#include "UI/UiController.h"
#include "UI/UiManager.h"
#include "UI/Button.h"
#include "overworld.hpp"
#include "audio/audio_manager.h"
#include "../system/game_event_handler.hpp"
#include "../system/input_handler.hpp"

using namespace UI::Controller;

class main_menu : public Scene
{

public:
	main_menu() : 
		Scene()
	{

		font.loadFromFile("../resources/font/arial.ttf");

		main_menu_ui = std::make_shared<MainMenuController>(font);

		auto ui = ServiceLocator::getService<UI::UiManager>();
		ui.push(main_menu_ui);

		if (!bg_texture.loadFromFile("../resources/title.jpg"))
		{
			std::cout << "Error load texture main menu background!" << std::endl;
		}

		bg_sprite.setTexture(bg_texture);

		auto audio = ServiceLocator::getService<AudioManager>();
		audio.add_bgm("main_bgm", "../resources/Audio/Big Day Out.ogg");
		audio.play_bgm("main_bgm", true, 50.f);

		button_setup();

		auto input = ServiceLocator::getService<InputManager>();
		main_menu_ui->onClick();
	}

	~main_menu()
	{
		std::cout << "main menu destroyed" << std::endl;
		main_menu_ui.reset();
	}

	virtual void update(float dt) override
	{
	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.draw(bg_sprite);
		main_menu_ui->draw(window);
	}

	void button_setup()
	{
		main_menu_ui->mm_view.new_game_button.setOnClickCb([this]
			{
				overworld_ = std::make_shared<Overworld>();
				ServiceLocator::getService<SceneManager>().load_scene(std::dynamic_pointer_cast<Scene>(overworld_));
				ServiceLocator::getService<UI::UiManager>().remove(main_menu_ui);
			});

		main_menu_ui->mm_view.load_game_button.setOnClickCb([this] {
				std::cout << "Custom On Load Game Clicked" << std::endl;
			});
		
		main_menu_ui->mm_view.settings_button.setOnClickCb([this] {
				std::cout << "Custom On Settings Clicked" << std::endl;
			});
		
		main_menu_ui->mm_view.quit_button.setOnClickCb([this] {
			ServiceLocator::getService<GameEventManager>().quitGame();
			});

	}

public:
	std::shared_ptr<MainMenuController> main_menu_ui;

private:
	std::shared_ptr<Overworld> overworld_;
	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
};