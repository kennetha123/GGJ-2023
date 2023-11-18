#include "ServiceLocator.h"
#include "system/entity.h"
#include "UI/UiController.h"
#include "UI/UiManager.h"
#include "UI/Button.h"
#include "Overworld.h"
#include "system/GameEventManager.h"
#include "system/InputManager.h"
#include "system/Observer.hpp"
using namespace UI::Controller;

class MainMenu : public Scene
{

public:
	MainMenu();
	~MainMenu();
	virtual void update(float dt) override;
	void buttonSetup();
public:
	std::shared_ptr<MainMenuController> main_menu_ui;

private:
	std::shared_ptr<spdlog::logger> log;
	std::shared_ptr<FpsController> fps_ctrl;
	std::shared_ptr<Overworld> overworld;
	sf::Sprite bg_sprite;
	sf::Texture bg_texture;
	sf::Font font;
	sf::View ui_camera;
};