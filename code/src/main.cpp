#include "header.h"

#include "scene/main_menu.hpp"
#include "game_context.hpp"

using namespace ui::controller;

void update_scene_and_ui(sf::Time dt);
void draw_game_objects(sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shatterpoint : Chaos Unbound");

    scene_manager& scene_manager_ = scene_manager::instance();
    ui::ui_manager& ui_manager_ = ui::ui_manager::instance();
    audio_manager& audio_manager_ = audio_manager::instance();
    input_handler input_handler_;
    game_event_handler event_handler_(window);

    sf::Clock clock;
    sf::Font font;

    game_context game_context_(ui_manager_, scene_manager_, audio_manager_, input_handler_, event_handler_);

    std::shared_ptr<main_menu> main_menu_ = std::make_shared<main_menu>(game_context_);

    font.loadFromFile("../resources/font/arial.ttf");
    std::shared_ptr<fps_controller> fps_ctrl = std::make_shared<fps_controller>(font);

    scene_manager_.load_scene(std::dynamic_pointer_cast<scene>(main_menu_));
    ui_manager_.push(fps_ctrl);

    sf::Event ev;

    while (window.isOpen())
    {
        input_handler_.handle_events(window, ev);

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
