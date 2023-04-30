#include "game_context.hpp"
#include "../system/ecs/entity.hpp"
#include "../ui/ui_models.hpp"
#include "../ui/button.hpp"
#include "overworld.hpp"

using namespace ui::controller;

class main_menu : public scene
{

public:
	main_menu(game_context& game_ctx) : 
		scene(game_ctx)
	{

		font.loadFromFile("../resources/font/arial.ttf");

		main_menu_ui = std::make_shared<main_menu_controller>(font);

		context.ui_manager_.push(main_menu_ui);

		if (!bg_texture.loadFromFile("../resources/title.jpg"))
		{
			std::cout << "Error load texture main menu background!" << std::endl;
		}

		bg_sprite.setTexture(bg_texture);

		context.audio_manager_.add_bgm("main_bgm", "../resources/Audio/Big Day Out.ogg");
		context.audio_manager_.play_bgm("main_bgm", true, 50.f);

		button_setup();

	}

	~main_menu()
	{
		std::cout << "main menu destroyed" << std::endl;
		main_menu_ui.reset();
	}

	virtual void update(float dt) override
	{
		main_menu_ui->on_click(context.input_handler_);
	}

	virtual void draw(sf::RenderWindow& window) override
	{
		window.draw(bg_sprite);
		main_menu_ui->draw(window);
	}

	void button_setup()
	{
		main_menu_ui->mm_view_.new_game_button.set_on_click_callback([this]
			{
				overworld_ = std::make_shared<overworld>(context);
				context.scene_manager_.load_scene(std::dynamic_pointer_cast<scene>(overworld_));
				context.ui_manager_.remove(main_menu_ui);
			});

		main_menu_ui->mm_view_.load_game_button.set_on_click_callback([this] {
				std::cout << "Custom On Load Game Clicked" << std::endl;
			});
		
		main_menu_ui->mm_view_.settings_button.set_on_click_callback([this] {
				std::cout << "Custom On Settings Clicked" << std::endl;
			});
		
		main_menu_ui->mm_view_.quit_button.set_on_click_callback([this] {
			context.event_handler_.quit_game();
			});

	}

public:
	std::shared_ptr<main_menu_controller> main_menu_ui;

private:
	std::shared_ptr<overworld> overworld_;
	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
};