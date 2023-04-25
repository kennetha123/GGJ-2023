#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../system/observer.hpp"

class Button : public sf::Drawable, public sf::Transformable, public Subject
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

        float width_diff = (bounds.width * 2.0f - bounds.width) / 2.0f;
        float height_diff = (bounds.height * 1.5f - bounds.height) / 2.0f;

        rectangleImage.setFillColor(sf::Color::Blue);
        rectangleImage.setSize(sf::Vector2f(bounds.width * 2.0f, bounds.height * 1.5f));
        rectangleImage.setPosition(x - width_diff, y - height_diff);
    }

    bool checkClick(const sf::Vector2f& mouse_position)
    {
        if (button_area.contains(mouse_position))
        {
            notify();
            return true;
        }

        return false;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(rectangleImage, states);
        target.draw(button_text, states);
    }

private:
    sf::Text button_text;
    sf::FloatRect button_area;
    sf::RectangleShape rectangleImage;
};
