#include "header.h"

#include "scene/MainMenu.h"
#include "ServiceLocator.h"
#include "utils/Time.h"
#include "UI/UiManager.h"
#include "audio/AudioManager.h"
#include "system/InputManager.h"
#include "system/GameEventManager.h"
#include "render/Renderer.h"

using namespace UI::Controller;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shatterpoint : Chaos Unbound");
    sf::RenderTexture render_texture;

    sf::Clock clock;
    sf::Font font;

    // Create services
    auto render_manager = std::make_shared<RenderManager>(window, render_texture);
    auto ui_manager = std::make_shared<UI::UiManager>();
    auto scene_manager = std::make_shared<SceneManager>();
    auto audio_manager = std::make_shared<AudioManager>();
    auto input_manager = std::make_shared<InputManager>();
    auto event_manager = std::make_shared<GameEventManager>(window);

    // Register services
    ServiceLocator::provide(render_manager);
    ServiceLocator::provide(ui_manager);
    ServiceLocator::provide(scene_manager);
    ServiceLocator::provide(audio_manager);
    ServiceLocator::provide(input_manager);
    ServiceLocator::provide(event_manager);

    std::shared_ptr<MainMenu> main_menu_ = std::make_shared<MainMenu>();

    font.loadFromFile("../resources/font/arial.ttf");
    std::shared_ptr<FpsController> fps_ctrl = std::make_shared<FpsController>(font);

    scene_manager->loadScene(std::dynamic_pointer_cast<Scene>(main_menu_));
    ui_manager->push(fps_ctrl);

    render_manager->registerRenderer(scene_manager);
    render_manager->registerRenderer(ui_manager);

    render_manager->initRenderer();

    sf::Event ev;

    while (window.isOpen())
    {
        input_manager->handleEvents(window, ev);

        sf::Time dt = clock.restart();
        dw::Time::setDeltaTime(dt.asSeconds());

        scene_manager->update(dt.asSeconds());
        ui_manager->update(dt.asSeconds());

        render_manager->draw();
    }
}