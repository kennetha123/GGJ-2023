#pragma once

#include <SFML/Graphics.hpp>
#include "../scene/scene_manager.hpp"

class main_menu;

class input_handler
{
public:
    input_handler(scene_manager& scene_manager_)
        : scene_manager_(scene_manager_)
    {
    }

    void handle_events(sf::RenderWindow& window)
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                auto mm_view_ptr = std::dynamic_pointer_cast<main_menu>(scene_manager_.current_scene());
                if (mm_view_ptr)
                {
                    mm_view_ptr->get_settings_button().checkClick(mouse_position);
                }
            }
        }
    }

private:
    scene_manager& scene_manager_;
};
