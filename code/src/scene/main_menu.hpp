#include "scene_manager.hpp"
#include "../system/ecs/entity.hpp"
#include "../ui/ui_manager.hpp"
#include "../ui/ui_models.hpp"

using namespace ui::controller;

class main_menu : public scene
{

public:
	main_menu(ui::ui_manager ui_mgr)
	{
		font.loadFromFile("../resources/font/arial.ttf");

		 main_menu_ctrl = std::make_shared<main_menu_controller>(font);

		 ui_mgr.push(main_menu_ctrl);

		 if (!bg_texture.loadFromFile("../resources/title.jpg"))
		 {
			 std::cout << "Error load texture main menu background!" << std::endl;
		 }

		 bg_sprite.setTexture(bg_texture);
	}

	// Inherited via scene
	virtual void update(float dt) override
	{

	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.draw(bg_sprite);
		main_menu_ctrl->draw(window);
	}

private:
	std::shared_ptr<main_menu_controller> main_menu_ctrl;

	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
};