#include "header.h"

#include "scene/main_menu.hpp"
#include "ServiceLocator.h"
#include "utils/Time.h"
#include "ui/ui_manager.hpp"
#include "audio/audio_manager.h"
#include "system/input_handler.hpp"
#include "system/game_event_handler.hpp"

using namespace UI::controller;

void update_scene_and_ui(sf::Time dt);
void draw_game_objects(sf::RenderWindow& window);

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

    std::shared_ptr<main_menu> main_menu_ = std::make_shared<main_menu>();

    font.loadFromFile("../resources/font/arial.ttf");
    std::shared_ptr<fps_controller> fps_ctrl = std::make_shared<fps_controller>(font);

    scene_manager->load_scene(std::dynamic_pointer_cast<Scene>(main_menu_));
    ui_manager->push(fps_ctrl);

    sf::Event ev;

    while (window.isOpen())
    {
        input_manager->handleEvents(window, ev);

        sf::Time dt = clock.restart();
        dw::Time::setDeltaTime(dt.asSeconds());
        update_scene_and_ui(dt);

        window.clear(sf::Color::Cyan);

        draw_game_objects(window);

        window.display();
    }
}

void update_scene_and_ui(sf::Time dt)
{
    ServiceLocator::getService<UI::UiManager>().update(dt.asSeconds());
    ServiceLocator::getService<SceneManager>().update(dt.asSeconds());
}

void draw_game_objects(sf::RenderWindow& window)
{
    ServiceLocator::getService<UI::UiManager>().draw(window);
    ServiceLocator::getService<SceneManager>().draw(window);
}
