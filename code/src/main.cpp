#include "header.h"

#include "scene/MainMenu.h"
#include "ServiceLocator.h"
#include "utils/Time.h"
#include "UI/UiManager.h"
#include "audio/AudioManager.h"
#include "system/InputManager.h"
#include "system/GameEventManager.h"
#include "render/Renderer.h"
#include "utils/Localization.h"
#include "system/Settings.h"
#include "utils/Logs.h"

using namespace UI::Controller;

void windowCreation(sf::RenderWindow& window, const sf::Vector2i& res, bool is_fullscreen);

int main()
{
   
    Logs::instance().log("main", spdlog::level::debug, "Start game Shatterpoint.");

    Settings setting;
    SettingData data = setting.loadSettings("../resources/settings/Settings.json");

    sf::RenderWindow window;
    windowCreation(window, sf::Vector2i(data.resolution.x, data.resolution.y), data.is_fullscreen);
    sf::RenderTexture render_texture;

    sf::Clock clock;
    sf::Font font;

    // Create services
    auto render_manager = std::make_shared<RenderManager>();
    auto ui_manager = std::make_shared<UI::UiManager>();
    auto scene_manager = std::make_shared<SceneManager>();
    auto audio_manager = std::make_shared<AudioManager>();
    auto input_manager = std::make_shared<InputManager>();
    auto event_manager = std::make_shared<GameEventManager>(window);
    auto localization = std::make_shared<Localization>("../resources/Localization/localization.json");
    
    // Register services
    ServiceLocator::provide(render_manager);
    ServiceLocator::provide(ui_manager);
    ServiceLocator::provide(scene_manager);
    ServiceLocator::provide(audio_manager);
    ServiceLocator::provide(input_manager);
    ServiceLocator::provide(event_manager);
    ServiceLocator::provide(localization);

    std::shared_ptr<MainMenu> main_menu_ = std::make_shared<MainMenu>();

    scene_manager->loadScene(std::dynamic_pointer_cast<Scene>(main_menu_));

    while (window.isOpen())
    {
        input_manager->handleEvents(window);

        sf::Time dt = clock.restart();
        dw::Time::setDeltaTime(dt.asSeconds());

        scene_manager->update(dt.asSeconds());
        ui_manager->update(dt.asSeconds());

        render_manager->draw(window);
    }

    // still a mystery, if you remove UIManager it will crash when MainMenu
    // got destroyed, so let smart pointer destruct itself automatically...
    ServiceLocator::remove<Localization>();
    ServiceLocator::remove<SceneManager>();
    ServiceLocator::remove<AudioManager>();
    ServiceLocator::remove<RenderManager>();
    ServiceLocator::remove<GameEventManager>();
    ServiceLocator::remove<InputManager>();
}


void windowCreation(sf::RenderWindow& window,const sf::Vector2i& res, bool is_fullscreen)
{
    if (is_fullscreen)
    {
        sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
        window.create(fullscreenMode, "Shatterpoint : Chaos Unbound", sf::Style::Fullscreen);
    }
    else 
    {
        sf::VideoMode windowedMode(res.x, res.y);
        window.create(windowedMode, "Shatterpoint : Chaos Unbound", sf::Style::Titlebar | sf::Style::Close);
    }
}