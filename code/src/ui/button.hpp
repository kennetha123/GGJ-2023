#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../system/observer.hpp"

class Button : public sf::Drawable, public sf::Transformable, public Observer
{
public:
    Button(const sf::Font& font, const std::string& text, float x, float y)
    {
        button_text.setFont(font);
        button_text.setString(text);
        button_text.setCharacterSize(30);
        button_text.setFillColor(sf::Color::White);
        button_text.setPosition(x, y);

        sf::FloatRect bounds = button_text.getGlobalBounds();
        button_area = sf::FloatRect(bounds.left, bounds.top, bounds.width, bounds.height);
    }

    bool checkClick(const sf::Vector2f& mouse_position)
    {
        if (button_area.contains(mouse_position))
        {
            onNotify();
            return true;
        }

        return false;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(button_text, states);
    }

    void onNotify() override
    {
        std::cout << "Settings function called" << std::endl;
    }

private:
    sf::Text button_text;
    sf::FloatRect button_area;
};
