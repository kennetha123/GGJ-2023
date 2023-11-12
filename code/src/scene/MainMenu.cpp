#include "scene/MainMenu.h"
#include <spdlog/spdlog.h>

MainMenu::MainMenu() :
	Scene(),
	ui_camera(sf::FloatRect(0, 0, 800, 600))
{
	log = spdlog::get("main");

	log->debug("MainMenu Constructor.");

	font.loadFromFile("../resources/font/NotoSansJP-Black.ttf");

	main_menu_ui = std::make_shared<MainMenuController>(font);

	auto& ui = ServiceLocator::getService<UI::UiManager>();

	fps_ctrl = std::make_shared<FpsController>(font);

	ui.push(main_menu_ui);
	ui.push(fps_ctrl);

	if (!bg_texture.loadFromFile("../resources/title.jpg"))
	{
		log->error("Error load texture main menu background!");
	}

	bg_sprite.setTexture(bg_texture);

	auto& audio = ServiceLocator::getService<AudioManager>();
	audio.addBgm("main_bgm", "../resources/Audio/Big Day Out.ogg");
	audio.playBgm("main_bgm", true, 50.f);

	buttonSetup();

	auto& input = ServiceLocator::getService<InputManager>();
	main_menu_ui->onClick();

	auto& render = ServiceLocator::getService<RenderManager>();
	render.addDrawable(bg_sprite, bg_sprite, RenderLayer::BACKGROUND, RenderBehavior::STATIC);
	render.setCamera(ui_camera);

	render.initRenderer(bg_sprite.getLocalBounds().width, bg_sprite.getLocalBounds().height);

}

MainMenu::~MainMenu()
{
	log->debug("MainMenu Destructor");
	auto& ui = ServiceLocator::getService<UI::UiManager>();

	ui.remove(main_menu_ui);
	ui.remove(fps_ctrl);
	main_menu_ui.reset();
}

void MainMenu::update(float dt)
{

}

void MainMenu::buttonSetup()
{
	main_menu_ui->mm_view.new_game_button->setOnClickCb([this]
		{
			overworld = std::make_shared<Overworld>();
			ServiceLocator::getService<SceneManager>().loadScene(std::dynamic_pointer_cast<Scene>(overworld));
			ServiceLocator::getService<UI::UiManager>().remove(main_menu_ui);
		});

	main_menu_ui->mm_view.load_game_button->setOnClickCb([this] {
		std::cout << "Custom On Load Game Clicked" << std::endl;
		});

	main_menu_ui->mm_view.settings_button->setOnClickCb([this] {
		std::cout << "Custom On Settings Clicked" << std::endl;
		});

	main_menu_ui->mm_view.quit_button->setOnClickCb([this] {
		ServiceLocator::getService<GameEventManager>().quitGame();
		});

}