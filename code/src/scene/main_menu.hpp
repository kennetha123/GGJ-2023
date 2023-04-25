#include "scene_manager.hpp"
#include "../system/ecs/entity.hpp"
#include "../ui/ui_manager.hpp"
#include "../ui/ui_models.hpp"
#include "../ui/button.hpp"

using namespace ui::controller;

class main_menu : public scene
{

public:
	main_menu(ui::ui_manager& ui_mgr)
	{
		font.loadFromFile("../resources/font/arial.ttf");

		main_menu_ui = std::make_shared<main_menu_controller>(font);

		ui_mgr.push(main_menu_ui);

		if (!bg_texture.loadFromFile("../resources/title.jpg"))
		{
			std::cout << "Error load texture main menu background!" << std::endl;
		}

		bg_sprite.setTexture(bg_texture);

		// Register all button
		ui_mgr.register_button(main_menu_ui->mm_view_.new_game_button);
		ui_mgr.register_button(main_menu_ui->mm_view_.load_game_button);
		ui_mgr.register_button(main_menu_ui->mm_view_.settings_button);
		ui_mgr.register_button(main_menu_ui->mm_view_.quit_button);
	}

	virtual void update(float dt) override
	{

	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.draw(bg_sprite);
		main_menu_ui->draw(window);
	}

public:
	std::shared_ptr<main_menu_controller> main_menu_ui;

private:

	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
};