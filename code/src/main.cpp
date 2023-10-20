#include "header.h"

#include "scene/MainMenu.h"
#include "ServiceLocator.h"
#include "utils/Time.h"
#include "UI/UiManager.h"
#include "audio/AudioManager.h"
#include "system/InputManager.h"
#include "system/GameEventManager.h"

using namespace UI::Controller;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shatterpoint : Chaos Unbound");

    sf::Clock clock;
    sf::Font font;

    // Create services
    auto ui_manager = std::make_shared<UI::UiManager>();
    auto scene_manager = std::make_shared<SceneManager>();
    auto audio_manager = std::make_shared<AudioManager>();
    auto input_manager = std::make_shared<InputManager>();
    auto event_manager = std::make_shared<GameEventManager>(window);

    // Register services
    ServiceLocator::provide(ui_manager);
    ServiceLocator::provide(scene_manager);
    ServiceLocator::provide(audio_manager);
    ServiceLocator::provide(input_manager);
    ServiceLocator::provide(event_manager);

    std::shared_ptr<MainMenu> main_menu_ = std::make_shared<MainMenu>();

    font.loadFromFile("../resources/font/arial.ttf");
    std::shared_ptr<FpsController> fps_ctrl = std::make_shared<FpsController>(font);

    scene_manager->load_scene(std::dynamic_pointer_cast<Scene>(main_menu_));
    ui_manager->push(fps_ctrl);

    sf::Event ev;

    while (window.isOpen())
    {
        input_manager->handleEvents(window, ev);

        sf::Time dt = clock.restart();
        dw::Time::setDeltaTime(dt.asSeconds());

        window.clear(sf::Color::Cyan);

        ui_manager->update(dt.asSeconds());
        scene_manager->update(dt.asSeconds());

        ui_manager->draw(window);
        scene_manager->draw(window);
        fps_ctrl->draw(window);

        window.display();
    }
}