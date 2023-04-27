#include "scene_manager.hpp"
#include "../system/ecs/entity.hpp"
#include "../ui/ui_manager.hpp"
#include "../ui/ui_models.hpp"
#include "../ui/button.hpp"

using namespace ui::controller;


class main_menu : public scene
{

public:
	main_menu()
	{
		ui::ui_manager& ui_manager = ui::ui_manager::instance();
		scene_manager& scene_manager_ = scene_manager::instance();

		font.loadFromFile("../resources/font/arial.ttf");

		main_menu_ui = std::make_shared<main_menu_controller>(font);

		ui_manager.push(main_menu_ui);

		if (!bg_texture.loadFromFile("../resources/title.jpg"))
		{
			std::cout << "Error load texture main menu background!" << std::endl;
		}

		bg_sprite.setTexture(bg_texture);

		// Register all button
		ui_manager.register_button(main_menu_ui->mm_view_.new_game_button);
		ui_manager.register_button(main_menu_ui->mm_view_.load_game_button);
		ui_manager.register_button(main_menu_ui->mm_view_.settings_button);
		ui_manager.register_button(main_menu_ui->mm_view_.quit_button);

		main_menu_ui->mm_view_.new_game_button.set_on_click_callback([this, &ui_manager, &scene_manager_]
			{
				overworld_ = std::make_shared<overworld>(ui_manager);
				scene_manager_.load_scene(std::dynamic_pointer_cast<scene>(overworld_));
				ui_manager.remove(main_menu_ui);
			});
		main_menu_ui->mm_view_.load_game_button.set_on_click_callback([this] {
			std::cout << "Custom On new game Clicked" << std::endl;
			});
		main_menu_ui->mm_view_.settings_button.set_on_click_callback([this] {
			std::cout << "Custom On Settings Clicked" << std::endl;
			});
		main_menu_ui->mm_view_.quit_button.set_on_click_callback([this] {
			});
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
		window_ = &window;
		window.draw(bg_sprite);
		main_menu_ui->draw(window);
	}

public:
	std::shared_ptr<main_menu_controller> main_menu_ui;

private:
	std::shared_ptr<overworld> overworld_;
	sf::RenderWindow* window_;
	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
};