#pragma once

#include <SFML/Graphics.hpp>
#include "../scene/scene_manager.hpp"

class main_menu;

class input_handler
{
public:
    input_handler(ui::ui_manager& ui_mgr) :
        ui_manager_(ui_mgr)
    {
    }

    void handle_events(sf::RenderWindow& window, sf::Event& ev)
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                ui_manager_.on_button_click(mouse_position);
            }
        }
    }

private:
    ui::ui_manager& ui_manager_;
};
