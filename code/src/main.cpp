#include "header.h"
#include "scene/scene_manager.hpp"
#include "scene/overworld.hpp"
#include "tile_manager.hpp"
#include "ui/ui_manager.hpp"
#include <SFML/Audio.hpp>
using namespace ui::controller;

void handle_window_events(sf::RenderWindow& window, sf::Event& ev);
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

    scene_manager scene_manager_;
    std::shared_ptr<overworld> ow = std::make_shared<overworld>();

    font.loadFromFile("../resources/font/arial.ttf");
    ui::ui_manager ui_mgr;
    std::shared_ptr<fps_controller> fps_view = std::make_shared<fps_controller>(font);

    scene_manager_.push_scene(std::dynamic_pointer_cast<scene>(ow));
    ui_mgr.push(fps_view);

    while (window.isOpen())
    {
        sf::Event ev;
        handle_window_events(window, ev);

        sf::Time dt = clock.restart();
        update_scene_and_ui(scene_manager_, ui_mgr, dt);

        window.clear();

        draw_game_objects(window, scene_manager_, ui_mgr);

        window.display();
    }
}

void handle_window_events(sf::RenderWindow& window, sf::Event& ev)
{
    while (window.pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            window.close();
        }
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
    scene_manager_.render(window);

    // draw ui
    ui_mgr.draw(window);
}
