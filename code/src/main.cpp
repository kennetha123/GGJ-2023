#include "header.h"
#include <SFML/Audio.hpp>

#include "scene/scene_manager.hpp"
#include "scene/overworld.hpp"
#include "scene/main_menu.hpp"
#include "tile_manager.hpp"
#include "ui/ui_manager.hpp"
#include "system/input_handler.hpp"

using namespace ui::controller;

void update_scene_and_ui(scene_manager& scene_manager_, ui::ui_manager& ui_mgr, sf::Time dt);
void draw_game_objects(sf::RenderWindow& window, scene_manager& scene_manager_, ui::ui_manager& ui_mgr);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shatterpoint : Chaos Unbound");
    sf::Clock clock;
    sf::Font font;

    // Load the background music
    sf::Music bgm;
    if (!bgm.openFromFile("../resources/Audio/Big Day Out.ogg"))
    {
        // Handle music loading error
        return -1;
    }

    // Configure the background music and play it
    bgm.setLoop(true); // Set the music to loop
    bgm.setVolume(50); // Set the volume (0 to 100)
    bgm.play();        // Start playing the music

    scene_manager& scene_manager_ = scene_manager::instance();
    ui::ui_manager& ui_manager_ = ui::ui_manager::instance();
    input_handler event_handler(ui_manager_);

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
        update_scene_and_ui(scene_manager_, ui_manager_, dt);

        window.clear();

        draw_game_objects(window, scene_manager_, ui_manager_);

        window.display();
    }
}

void update_scene_and_ui(scene_manager& scene_manager_, ui::ui_manager& ui_mgr, sf::Time dt)
{
    scene_manager_.update(dt.asSeconds());
    ui_mgr.update(dt.asSeconds());
}

void draw_game_objects(sf::RenderWindow& window, scene_manager& scene_manager_, ui::ui_manager& ui_mgr)
{

    // draw scene object
    scene_manager_.draw(window);

    // draw ui
    ui_mgr.draw(window);
}
