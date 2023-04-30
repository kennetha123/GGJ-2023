#pragma once

#include <SFML/Graphics.hpp>
#include "../scene/scene_manager.hpp"

class main_menu;

class input_handler
{
public:
    input_handler()
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
                right_click_action(ev, mouse_position);
            }
        }
    }

    void set_right_click(std::function<void(sf::Event&, const sf::Vector2f& mouse_position)> action)
    {
        right_click_action = action;
    }
private:
    std::function<void(sf::Event&, const sf::Vector2f& mouse_position)> right_click_action;


};
