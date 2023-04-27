#include "header.h"
#include <SFML/Audio.hpp>

#include "scene/scene_manager.hpp"
#include "scene/overworld.hpp"
#include "scene/main_menu.hpp"
#include "tile_manager.hpp"
#include "ui/ui_manager.hpp"
#include "system/input_handler.hpp"

using namespace ui::controller;

void update_scene_and_ui(sf::Time dt);
void draw_game_objects(sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shatterpoint : Chaos Unbound");
    sf::Clock clock;
    sf::Font font;

    scene_manager& scene_manager_ = scene_manager::instance();
    ui::ui_manager& ui_manager_ = ui::ui_manager::instance();

    input_handler event_handler;

    std::shared_ptr<main_menu> main_menu_ = std::make_shared<main_menu>();

    font.loadFromFile("../resources/font/arial.ttf");
    std::shared_ptr<fps_controller> fps_ctrl = std::make_shared<fps_controller>(font);

    scene_manager_.load_scene(std::dynamic_pointer_cast<scene>(main_menu_));
    ui_manager_.push(fps_ctrl);

    sf::Event ev;

    while (window.isOpen())
    {
        event_handler.handle_events(window, ev);

        sf::Time dt = clock.restart();
        update_scene_and_ui(dt);

        window.clear();

        draw_game_objects(window);

        window.display();
    }
}

void update_scene_and_ui(sf::Time dt)
{
    ui::ui_manager::instance().update(dt.asSeconds());
    scene_manager::instance().update(dt.asSeconds());
}

void draw_game_objects(sf::RenderWindow& window)
{
    scene_manager::instance().draw(window);
    ui::ui_manager::instance().draw(window);
}
